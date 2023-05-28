#pragma once

#include <stdint.h>
#include "BootInformation.hpp"

// Memory manager assumes that the kernel is located at the 1MiB mark in memory.
class PhysicalMemoryManager
{
public:
    void* allocateAddress();
    void freeAddress(void* address);

    explicit PhysicalMemoryManager(const BootInformation& bootInformation);

private:
    void* myStartAddress;
    uint32_t myTotalBlocks;
    uint32_t* myBitMap;
    uint32_t myCurrentBlock;

    void freeBlock(uint32_t block);
    void reserveBlock(uint32_t block);
    void* blockToAddress(uint32_t block);
    uint32_t addressToBlock(void* address);
};
