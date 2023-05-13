#include "PhysicalMemoryManager.hpp"
#include "TextBuffer.hpp"

PhysicalMemoryManager::PhysicalMemoryManager(const BootInformation& bootInformation,
        TextBuffer& textBuffer) :
        myTextBuffer{textBuffer}
{
    extern uint32_t kernelEnd;
    uint32_t kernelEndValue = (uint32_t) (&kernelEnd);

    const uint32_t oneMiB = 1048576;

    myStartAddress = (uint8_t*)(oneMiB);
    myTotalBlocks = (bootInformation.memoryUpper + 3)/4;
    myTotalBlocks = myTotalBlocks - (myTotalBlocks % 32);
    uint32_t kernelBlocks =  (kernelEndValue - oneMiB + 4095)/4096;
    uint32_t bitsPer4KiBBlock = 32768;
    myBitArray = (uint32_t*)(oneMiB + (4096 * kernelBlocks));
    uint32_t usedBlocks =  kernelBlocks + (myTotalBlocks + bitsPer4KiBBlock - 1) / bitsPer4KiBBlock;

    for (uint32_t blockMap{0}; blockMap < myTotalBlocks/32; blockMap++)
    {
        uint32_t* currentBitMap = myBitArray + blockMap;
        *currentBitMap = 0;
    }
    for (uint32_t blockID{0}; blockID < usedBlocks; blockID++)
    {
        reserveBlock(blockID);
    }
    myCurrentBlock = usedBlocks;
}

void PhysicalMemoryManager::reserveBlock(uint32_t block)
{
    uint32_t* blockBitArray = myBitArray + (block/32);
    *blockBitArray |= (0x1 << (block % 32));
}

void PhysicalMemoryManager::freeBlock(uint32_t block)
{
    uint32_t* blockBitArray = myBitArray + (block/32);
    *blockBitArray &= ~(1 << (block % 32));
}

void* PhysicalMemoryManager::allocateAddress()
{
    uint32_t* blockBitArray = myBitArray + (myCurrentBlock / 32);
    for (uint32_t numberTested; numberTested < myTotalBlocks; numberTested++)
    {
        if((myCurrentBlock % 32) == 0)
        {
            blockBitArray = myBitArray + (myCurrentBlock / 32);
        }
        //wrong
        if(!(*blockBitArray & (1 << myCurrentBlock % 32)))
        {
            reserveBlock(myCurrentBlock);
            return blockToAddress(myCurrentBlock);
        }
        myCurrentBlock++;
    }
    // TODO: Raise Exception.
}

void PhysicalMemoryManager::freeAddress(void* address)
{
    freeBlock(addressToBlock(address));
}

void* PhysicalMemoryManager::blockToAddress(uint32_t block)
{
    return (void*)((uint8_t*)myStartAddress + (block * 4096));
}

uint32_t PhysicalMemoryManager::addressToBlock(void* address)
{
    return ((uint8_t*)address - (uint8_t*)myStartAddress)/4096;
}

