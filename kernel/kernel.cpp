#include "stddef.h"

extern "C"
{

#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "VGATextModeBuffer.hpp"
#include "MemoryAllocator.hpp"

void main(uint32_t cpuidFeaturesEDX, uint32_t cpuidFeaturesECX, uint32_t grubMagicNumber, void* grubBootInformationAddress) 
{

    if (grubMagicNumber != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }

    BootInformation bootInformation(grubBootInformationAddress);

    if (bootInformation.framebufferType == 2)
    {
        VGATextModeBuffer textBuffer{};
        textBuffer.writeString("VGA text buffer.");
    }
    else if (bootInformation.framebufferType == 1)
    {
        DirectDisplayTextBuffer textBuffer{bootInformation};
        textBuffer.writeString("Direct display text buffer.\n");

        extern void* kernelStart;
        const uint64_t kernelStartAddress {reinterpret_cast<uint64_t>(&kernelStart)};
        textBuffer.writeString("\nKernel start : ");
        textBuffer.writeHex(kernelStartAddress);

        extern void* kernelEnd;
        const uint64_t kernelEndAddress {reinterpret_cast<uint64_t>(&kernelEnd)};
        textBuffer.writeString("\nKernel end : ");
        textBuffer.writeHex(kernelEndAddress);

        MemoryAllocatorNode* node = MemoryAllocator::instance().myRootAddress;
        if (node == nullptr)
        {
            textBuffer.writeString("\nMemory allocator empty.");
        }
        while (node != nullptr)
        {
            textBuffer.writeString("\nAddress : ");
            textBuffer.writeHex(reinterpret_cast<uint64_t>(node));
            textBuffer.writeString("  | length : ");
            textBuffer.writeHex(node->size);
            node = node->nextAddress;
        }
    }
}
}
