#include "MemoryAllocator.hpp"

MemoryAllocator::MemoryAllocator(const BootInformation& bootInformation, DirectDisplayTextBuffer& textBuffer) :
        myRootAddress{nullptr}
{
    extern void* kernelStart;
    const uint64_t kernelStartAddress = reinterpret_cast<uint64_t>(&kernelStart);
    textBuffer.writeString("\n Kernel start: ");
    textBuffer.writeHex(kernelStartAddress);

    extern void* kernelEnd;
    const uint64_t kernelEndAddress = reinterpret_cast<uint64_t>(&kernelEnd);
    textBuffer.writeString("\n Kernel end : ");
    textBuffer.writeHex(kernelEndAddress);

    auto linkMemory = [this, bootInformation](const uint64_t& address, const uint64_t& length)
    {
        MemoryAllocatorNode*& trace = myRootAddress;
        // Finds the first node without a subsequent node
        while (trace != nullptr)
        {
            trace = trace->nextAddress;
        }
        trace = reinterpret_cast<MemoryAllocatorNode*>(address);
        trace->length = length;
        trace->nextAddress = nullptr;
    };

    for (uint32_t i = 0; i < bootInformation.numEntries; i++)
    {
        uint64_t address = bootInformation.entries[i].baseAddress;
        uint64_t length = bootInformation.entries[i].length;
        // Ensures the entry is free ram and has space to store the memory node information,
        //      ignores memory rooted at nullptr
        if (bootInformation.entries[i].type == 1 && length > sizeof(MemoryAllocatorNode) && address != 0)
        {
            if (address <= kernelEndAddress && address + length >= kernelEndAddress)
            {
                length = length - (kernelEndAddress - address - 1);
                address = kernelEndAddress + 1;
            }
            linkMemory(address, length);
        }
    }
}

