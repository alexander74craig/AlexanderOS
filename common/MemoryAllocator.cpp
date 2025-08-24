#include "MemoryAllocator.hpp"



uint64_t inline MemoryAllocator::align(const uint64_t toAlign)
{
    return (toAlign + 15) & ~15;
}

void inline MemoryAllocator::alignBlock(uint64_t& address, uint64_t& size)
{
    // Aligns address and truncates size accordingly.
    uint64_t alignedAddress = align(address);
    if (alignedAddress > address)
    {
        uint64_t diff = alignedAddress - address;
        address = alignedAddress;
        if (size < diff)
        {
            size = 0;
        }
        else
        {
            size -= diff;
        }
    }

    // Rounds size down to nearest multiple of 16
    size &= ~15;

    address = alignedAddress;
}

void MemoryAllocator::linkMemory(uint64_t address, uint64_t size)
{
    alignBlock(address, size);

    // Don't link if the size cannot fit a node
    if (size < sizeof(MemoryAllocatorNode))
    {
        return;
    }

    // Prevent linking code directly at the nullptr
    if (address == 0)
    {
        if (size <= 16)
        {
            return;
        }
        size -= 16;
        address = 16;
    }

    // If the root node has been initialized, link the new memory segment
    if (myRootAddress != nullptr)
    {
        MemoryAllocatorNode* trace = myRootAddress;
        MemoryAllocatorNode* previous = nullptr;

        // Find the location where the new segment fits sequentially.
        while ( trace != nullptr && reinterpret_cast<uint64_t>(trace) < address)
        {
            previous = trace;
            trace = trace->nextAddress;
        }

        MemoryAllocatorNode* newNode = reinterpret_cast<MemoryAllocatorNode*>(address);

        // If adjacent to succeeding node, coalesce it, otherwise link to it.
        if (address + size == reinterpret_cast<uint64_t>(trace))
        {
            newNode->size = size + trace->size;
            newNode->nextAddress = trace->nextAddress;
        }
        else
        {
            newNode->size = size;
            newNode->nextAddress = trace;
        }
        if (previous != nullptr)
        {
            // If adjacent to preceding node, coalesce, otherwise link
            if (reinterpret_cast<uint64_t>(previous) + previous->size == address)
            {
                previous->size += newNode->size;
                previous->nextAddress = newNode->nextAddress;
            }
            else
            {
                previous->nextAddress = newNode;
            }
        }
        else
        {
            myRootAddress = newNode;
        }
    }
    // Initialize root address
    else // (myRootAddress == nullptr)
    {
        myRootAddress = reinterpret_cast<MemoryAllocatorNode*>(address);
        myRootAddress->size = size;
        myRootAddress->nextAddress = nullptr;
    }
}

void* MemoryAllocator::alloc(size_t size)
{
    // Minimum size to hold memory allocator
    if (size < sizeof(MemoryAllocatorNode))
    {
        size = sizeof(MemoryAllocatorNode);
    }
    size = align(size);
    MemoryAllocatorNode* trace = myRootAddress;
    MemoryAllocatorNode* previous = nullptr;
    while (trace != nullptr)
    {
        if (trace->size >= size)
        {
            trace->size -= size;
            if (trace->size == 0)
            {
                if (previous != nullptr)
                {
                    previous->nextAddress = trace->nextAddress;
                }
                else
                {
                    myRootAddress = trace->nextAddress;
                }
            }
            return (reinterpret_cast<uint8_t*>(trace) + trace->size);
        }
        previous = trace;
        trace = trace->nextAddress;
    }
    return nullptr;
}

void MemoryAllocator::free(void* ptr, size_t size)
{
    if (size < sizeof(MemoryAllocatorNode))
    {
        size = sizeof(MemoryAllocatorNode);
    }
    size = align(size);
    linkMemory(reinterpret_cast<uint64_t>(ptr), size);
}

void MemoryAllocator::intitializeMemory(const MemoryList& memory)
{
    for (size_t i = 0; i < memory.size(); i++)
    {
        linkMemory(memory.at(i).address, memory.at(i).size);
    }
    //TODO: Track total memory added
}

uint64_t MemoryAllocator::getMemorySize() const
{
    MemoryAllocatorNode* trace = myRootAddress;
    uint64_t size = 0;
    while (trace != nullptr)
    {
        size += trace->size;
        trace = trace->nextAddress;
    }
    return size;
}
uint64_t MemoryAllocator::getFragmentation() const
{
    MemoryAllocatorNode* trace = myRootAddress;
    uint64_t fragmentation{0};
    while (trace != nullptr)
    {
        fragmentation++;
        trace = trace->nextAddress;
    }
    return fragmentation;
}
