#include "PhysicalMemoryManager.hpp"
#include "TextBuffer.hpp"

PhysicalMemoryManager::PhysicalMemoryManager(const BootInformation& bootInformation, TextBuffer& textBuffer)
{
    extern uint32_t kernelEnd;
    uint32_t kernelEndValue = (uint32_t) (&kernelEnd);

    const uint32_t oneMiB = 1048576;
    const uint32_t bitsPer4KiBBlock = 32768;

    // Address of 1MiB
    myStartAddress = (uint8_t*)(oneMiB);

    // Calculates total blocks as number of 4KiB memory chunks as groups of 32 chunks.
    myTotalBlocks = (bootInformation.memoryUpper + 3)/4;
    myTotalBlocks = myTotalBlocks - (myTotalBlocks % 32);

    // Number of blocks necessary to store the kernel
    uint32_t kernelBlocks =  (kernelEndValue - oneMiB + 4095)/4096;


    // Address of bitmap
    myBitMap = (uint32_t*)(oneMiB + (4096 * kernelBlocks));

    // Number of blocks to store bitmaps detailing the total amount of memory available
    uint32_t usedBlocks =  kernelBlocks + (myTotalBlocks + bitsPer4KiBBlock - 1) / bitsPer4KiBBlock;

    for (uint32_t blockMap{0}; blockMap < myTotalBlocks/32; blockMap++)
    {
        uint32_t* currentBitMap = myBitMap + blockMap;
        *currentBitMap = 0;
    }
    uint32_t mapIndex{0};
    while ((bootInformation.memoryMapEntries[mapIndex].length != 0) && (mapIndex < 64))
    {
        auto& mapEntry = bootInformation.memoryMapEntries[mapIndex];
        // If map entry is not usable memory, reserve all affected blocks.
        if ((mapEntry.type != 1) && (mapEntry.baseAddress > oneMiB))
        {
            uint32_t startBlock = (mapEntry.baseAddress - oneMiB) / 4096;
            uint32_t endBlock = (mapEntry.baseAddress + mapEntry.length - oneMiB - 1) / 4096;
            while (startBlock <= endBlock && startBlock < myTotalBlocks)
            {
                reserveBlock(startBlock);
                startBlock++;
            }
        }
        mapIndex++;
    }
    for (uint32_t blockID{0}; blockID < usedBlocks; blockID++)
    {
        reserveBlock(blockID);
    }
    myCurrentBlock = usedBlocks;
}

void PhysicalMemoryManager::reserveBlock(uint32_t block)
{
    uint32_t* blockBitArray = myBitMap + (block/32);
    *blockBitArray |= (0x1 << (block % 32));
}

void PhysicalMemoryManager::freeBlock(uint32_t block)
{
    uint32_t* blockBitArray = myBitMap + (block/32);
    *blockBitArray &= ~(1 << (block % 32));
}

void* PhysicalMemoryManager::allocateAddress()
{
    uint32_t* blockBitArray = myBitMap + (myCurrentBlock / 32);
    for (uint32_t numberTested{0}; numberTested < myTotalBlocks; numberTested++)
    {
        if((myCurrentBlock % 32) == 0)
        {
            blockBitArray = myBitMap + (myCurrentBlock / 32);
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

