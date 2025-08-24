extern "C"
{

#include "stddef.h"
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
    MemoryAllocator::instance().intitializeMemory(bootInformation.getFreeMemory());
    TextBuffer* textBuffer{nullptr};


    if (bootInformation.getFrameBuffer().type == 2)
    {
        textBuffer = new VGATextModeBuffer{};
        textBuffer->writeString("VGA text buffer.");
    }
    else if (bootInformation.getFrameBuffer().type == 1)
    {
        textBuffer = new DirectDisplayTextBuffer{bootInformation.getFrameBuffer()};
        textBuffer->writeString("Direct display text buffer.");
    }

    const MemoryList& freeMemory {bootInformation.getFreeMemory()};
    for (size_t i = 0; i < freeMemory.size(); i++)
    {
        textBuffer->writeString("\nMemory block : ");
        textBuffer->writeHex(freeMemory.at(i).address);
        textBuffer->writeString("  | length : ");
        textBuffer->writeHex(freeMemory.at(i).size);
    }

    textBuffer->writeString("\nMemory allocator free memory: ");
    textBuffer->writeHex(MemoryAllocator::instance().getMemorySize());
}
}
