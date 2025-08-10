//
// Created by alex on 8/8/25.
//

#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator(const BootInformation& bootInformation) :
        myRootAddress{nullptr},
        myRootSize{0}
{
    for (uint32_t i = 0; i < bootInformation.numEntries; i++)
    {
        if (bootInformation.entries[i].type == 1) {
        }
    }
}