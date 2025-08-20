#pragma once
#include "stdint.h"
#include "stddef.h"


struct MemoryBlock
{
    MemoryBlock(uint64_t address, uint64_t size) : address{address}, size{size} {};
    MemoryBlock() : address{0}, size{0} {};
    uint64_t address;
    uint64_t size;
};

class MemoryList
{
public:
    MemoryList();
    void pushBack(const MemoryBlock& block);
    size_t size() const;
    MemoryBlock at(size_t index) const;
private:
    MemoryBlock myMemory[128];
    size_t mySize;
};