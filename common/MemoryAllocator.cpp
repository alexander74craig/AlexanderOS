#include "MemoryAllocator.hpp"

MemoryAllocator::MemoryAllocator(const MemoryList& memoryList) :
        myRootAddress{nullptr}
{
    for (size_t i = 0; i < memoryList.size(); i++)
    {
        linkMemory(memoryList.at(i).address, memoryList.at(i).size);
    }
}

//Should be used by both initialization and freeing.
void MemoryAllocator::linkMemory(uint64_t address, uint64_t size)
{
    if (size <= sizeof(MemoryAllocatorNode))
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
        // Finds the first node without a subsequent node
        while (trace->nextAddress != nullptr)
        {
            trace = trace->nextAddress;
        }
        trace->nextAddress = reinterpret_cast<MemoryAllocatorNode*>(address);
        trace->nextAddress->size = size - sizeof(MemoryAllocatorNode);
        trace->nextAddress->nextAddress = nullptr;
    }
}
