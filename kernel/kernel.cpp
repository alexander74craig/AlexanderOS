#include "stddef.h"

extern "C"
{

#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "VGATextModeBuffer.hpp"
#include "MemoryAllocator.hpp"

//! \brief Main entry point of the kernel.
//! \param[in] cpuidFeaturesEDX The CPUID feature flags from the EDX register.
//! \param[in] cpuidFeaturesECX The CPUID feature flags from the ECX register
//! \param[in] grubMagicNumber  Multiboot 2 Magic number
//! \param[in] grubBootInformationAddress Location of Multiboot 2 header
void main(uint32_t cpuidFeaturesEDX, uint32_t cpuidFeaturesECX, uint32_t grubMagicNumber, void* grubBootInformationAddress) 
{

    if (grubMagicNumber != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }
    BootInformation bootInformation(grubBootInformationAddress);

    if (bootInformation.getFrameBuffer().type == 2)
    {
        VGATextModeBuffer textBuffer{};
        textBuffer.writeString("VGA text buffer.");
    }
    else if (bootInformation.getFrameBuffer().type == 1)
    {
        DirectDisplayTextBuffer textBuffer{bootInformation.getFrameBuffer()};
        textBuffer.writeString("Direct display text buffer.");

        textBuffer.writeString("\nMultiBoot2 address: ");
        textBuffer.writeHex(reinterpret_cast<uint64_t>(grubBootInformationAddress));

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
