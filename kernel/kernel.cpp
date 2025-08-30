#include <CPUID.hpp>
#include <SerialTextBuffer.hpp>

extern "C"
{

#include "stddef.h"
#include "BootInformation.hpp"
#include "DirectRGBTextBuffer.hpp"
#include "EGATextBuffer.hpp"
#include "MemoryAllocator.hpp"

//! \brief Main entry point of the kernel.
//! \param[in] grubMagicNumber  Multiboot 2 Magic number
//! \param[in] grubBootInformationAddress Location of Multiboot 2 header
void main(uint32_t grubMagicNumber, void* grubBootInformationAddress)
{
    // Enable interrupts
    asm("sti");

    if (grubMagicNumber != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }

    BootInformation bootInformation(grubBootInformationAddress);
    auto freeMemory {bootInformation.getFreeMemory()};
    MemoryAllocator::instance().initializeMemory(bootInformation.getFreeMemory());

    TextBuffer* textBuffer{};
    if (bootInformation.getFrameBuffer().type == FrameBufferType::EGA)
    {
        textBuffer = new EGATextBuffer{};
    }
    else if (bootInformation.getFrameBuffer().type == FrameBufferType::Direct)
    {
        textBuffer = new DirectRGBTextBuffer{bootInformation.getFrameBuffer()};
    }
    else
    {
        textBuffer = new SerialTextBuffer{SerialPort::COM1};
    }

    textBuffer->write("Free memory: ");
    for (size_t i{0}; i < freeMemory.size(); i++)
    {
        textBuffer->write("\naddress: ");
        textBuffer->write(freeMemory.at(i).address);
        textBuffer->write(" size: ");
        textBuffer->write(freeMemory.at(i).size);
    }

    textBuffer->write("\nMemory allocator total memory: ");
    textBuffer->write(MemoryAllocator::instance().getTotalMemorySize());

    textBuffer->write("\nMemory allocator free memory: ");
    textBuffer->write(MemoryAllocator::instance().getFreeMemorySize());

    textBuffer->write("\nFramebuffer address: ");
    textBuffer->write(reinterpret_cast<uint64_t>(bootInformation.getFrameBuffer().address));

    CPUID cpuid;
    textBuffer->write("\nCan 1GiB Pages: ");
    textBuffer->write(cpuid.canHave1GiBPages());

    delete textBuffer;
}
}
