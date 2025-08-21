#include "MemoryAllocator.hpp"

void MemoryAllocator::linkMemory(uint64_t address, uint64_t size)
{
    if (size < sizeof(MemoryAllocatorNode))
    {
        return;
    }
    if (address == 0)
    {
        if (size > 2 + sizeof(MemoryAllocatorNode))
        {
            address += 2;
            size -= 2;
        }
        else
        {
            return;
        }
    }
    if (myRootAddress == nullptr)
    {
        myRootAddress = reinterpret_cast<MemoryAllocatorNode*>(address);
        myRootAddress->size = size - sizeof(MemoryAllocatorNode);
        myRootAddress->nextAddress = nullptr;
    }
    else
    {
        MemoryAllocatorNode* trace = myRootAddress;
        // TODO: Find correct position for block that keep memory addresses in order
        while (trace->nextAddress != nullptr)
        {
            trace = trace->nextAddress;
        }
        //TODO: Check if contiguous with link and combine if so
        if (trace->nextAddress == nullptr)
        {
            trace->nextAddress = reinterpret_cast<MemoryAllocatorNode*>(address);
            trace->nextAddress->size = size - sizeof(MemoryAllocatorNode);
            trace->nextAddress->nextAddress = nullptr;
        }
        else
        {
            const auto previousNext = trace->nextAddress;
            trace->nextAddress = reinterpret_cast<MemoryAllocatorNode*>(address);
            trace->nextAddress->size = size - sizeof(MemoryAllocatorNode);
            trace->nextAddress->nextAddress = previousNext;
        }
    }
}

void* MemoryAllocator::alloc(size_t size)
{
    //TODO: Multiples of 16 to align
    if (size < sizeof(MemoryAllocatorNode))
    {
        size = sizeof(MemoryAllocatorNode);
    }
    MemoryAllocatorNode* trace = myRootAddress;
    while (trace != nullptr)
    {
        if (trace->size >= size)
        {
            trace->size -= size;
            return (reinterpret_cast<uint8_t*>(trace) + trace->size);
        }
        trace = trace->nextAddress;
    }
    return nullptr;
}

void MemoryAllocator::free(void* ptr, size_t size)
{
    //TODO: Multiples of 16 to align
    if (size < sizeof(MemoryAllocatorNode))
    {
        size = sizeof(MemoryAllocatorNode);
    }
    linkMemory(reinterpret_cast<uint64_t>(ptr), size);
}
