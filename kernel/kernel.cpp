#include <SerialTextBuffer.hpp>

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
    VGATextModeBuffer textBuffer;
    textBuffer.writeString("Free memory: ");
    for (size_t i{0}; i < freeMemory.size(); i++)
    {
        textBuffer.writeString("\naddress: ");
        textBuffer.writeHex(freeMemory.at(i).address);
        textBuffer.writeString(" size: ");
        textBuffer.writeHex(freeMemory.at(i).size);
    }

    MemoryAllocator::instance().initializeMemory(bootInformation.getFreeMemory());

    textBuffer.writeString("\nMemory allocator total memory: ");
    textBuffer.writeHex(MemoryAllocator::instance().getTotalMemorySize());

    textBuffer.writeString("\nMemory allocator free memory: ");
    textBuffer.writeHex(MemoryAllocator::instance().getFreeMemorySize());

    SerialTextBuffer serial{SerialPort::COM1};
    serial.writeString("Hello world!\n");
}
}
