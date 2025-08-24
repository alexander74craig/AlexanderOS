#include "Memory.hpp"
MemoryList::MemoryList() :
        mySize{0}
{
}

void MemoryList::pushBack(const MemoryBlock &block)
{
    if (mySize < 128)
    {
        myMemory[mySize] = block;
        mySize++;
    }
}

size_t MemoryList::size() const
{
    return mySize;
}

MemoryBlock MemoryList::at(size_t index) const
{
    if (index < mySize)
    {
        return myMemory[index];
    }
    return MemoryBlock{};
}