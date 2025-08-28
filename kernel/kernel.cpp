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
    auto freeMemory {bootInformation.getFreeMemory()};
    VGATextModeBuffer::instance().writeString("Free memory: ");
    for (size_t i{0}; i < freeMemory.size(); i++)
    {
        VGATextModeBuffer::instance().writeString("\naddress: ");
        VGATextModeBuffer::instance().writeHex(freeMemory.at(i).address);
        VGATextModeBuffer::instance().writeString(" size: ");
        VGATextModeBuffer::instance().writeHex(freeMemory.at(i).size);
    }

    MemoryAllocator::instance().initializeMemory(bootInformation.getFreeMemory());

    VGATextModeBuffer::instance().writeString("\nMemory allocator total memory: ");
    VGATextModeBuffer::instance().writeHex(MemoryAllocator::instance().getTotalMemorySize());

    VGATextModeBuffer::instance().writeString("\nMemory allocator free memory: ");
    VGATextModeBuffer::instance().writeHex(MemoryAllocator::instance().getFreeMemorySize());
}
}
