//
// Created by alex on 8/8/25.
//

#include "MemoryAllocator.h"

MemoryAllocator::MemoryAllocator(const BootInformation& bootInformation, DirectDisplayTextBuffer& textBuffer) :
        myRootAddress{nullptr}
{
    for (uint32_t i = 0; i < bootInformation.numEntries; i++)
    {
        textBuffer.writeString("\nA");
        // Ensures the entry is free ram and has space to store the memory node information
        if (bootInformation.entries[i].type == 1 &&
                bootInformation.entries[i].length > sizeof(MemoryAllocatorNode))
        {
            textBuffer.writeString("\nB");
            MemoryAllocatorNode* trace = myRootAddress;
            // Finds the first node without a subsequent node
            while (trace != nullptr)
            {
                textBuffer.writeString("\nC");
                trace = trace->nextAddress;
            }

            textBuffer.writeString("\nD");
            trace = reinterpret_cast<MemoryAllocatorNode*>(bootInformation.entries[i].baseAddress);
            trace->size = bootInformation.entries[i].length - sizeof(MemoryAllocatorNode);
            trace->nextAddress = nullptr;
            if (trace == nullptr)
            {
                textBuffer.writeString("\nE");
            }
        }
    }
}
