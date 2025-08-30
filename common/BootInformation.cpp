#include "BootInformation.hpp"

#include <MemoryAllocator.hpp>

BootInformation::BootInformation(void* ebx) :
    myEbx{ebx}
{
    // Total size of boot information
    uint32_t total_size(readUint32());
    //Reserved 0s
    readUint32();

    uint32_t currentSize{8};
    while(currentSize < total_size)
    {
        // Tag type
        const uint32_t type{readUint32()};

        // Size in bytes.
        const uint32_t size{readUint32()};

        uint32_t dataSize = size - 8;
        // Checks for padding to maintain tag alignment
        if (dataSize % 8 != 0)
        {
            dataSize = dataSize + (8 - (dataSize % 8));
        }
        if (type == 8)
        {
            readFramebuffer(dataSize);
        }
        else if (type == 6)
        {
            readMemoryMap(dataSize);
        }
        else 
        {
            // Skips over the current data section
            myEbx = static_cast<uint8_t *>(myEbx) + dataSize;
        }
        // Adds size plus padding to current size of data read.
        currentSize += dataSize + 8;
    }
}



uint64_t BootInformation::readUint64()
{
    const uint64_t returnInt{*static_cast<uint64_t *>(myEbx)};
    myEbx = static_cast<uint64_t *>(myEbx) + 1;
    return returnInt;
}
uint32_t BootInformation::readUint32()
{
    const uint32_t returnInt{*static_cast<uint32_t *>(myEbx)};
    myEbx = static_cast<uint32_t *>(myEbx) + 1;
    return returnInt;
}
uint16_t BootInformation::readUint16()
{
    const uint16_t returnInt{*static_cast<uint16_t *>(myEbx)};
    myEbx = static_cast<uint16_t *>(myEbx) + 1;
    return returnInt;
}
uint8_t BootInformation::readUint8()
{
    const uint8_t returnInt{*static_cast<uint8_t *>(myEbx)};
    myEbx = static_cast<uint8_t *>(myEbx) + 1;
    return returnInt;
}

void BootInformation::readFramebuffer(uint32_t dataSize)
{
    myFrameBuffer.address = reinterpret_cast<uint8_t*>(readUint64());
    myFrameBuffer.pitch = readUint32();
    myFrameBuffer.width = readUint32();
    myFrameBuffer.height = readUint32();
    myFrameBuffer.bitsPerPixel = readUint8();
    uint8_t type = readUint8();
    if (type == static_cast<uint8_t>(FrameBufferType::Direct))
    {
        myFrameBuffer.type = FrameBufferType::Direct;
    }
    else if (type == static_cast<uint8_t>(FrameBufferType::EGA))
    {
        myFrameBuffer.type = FrameBufferType::EGA;
    }
    else if (type == static_cast<uint8_t>(FrameBufferType::Palette))
    {
        myFrameBuffer.type = FrameBufferType::Palette;
    }
    // Reserved 2 bytes
    readUint16();
    // Direct Display type
    if (myFrameBuffer.type == FrameBufferType::Direct)
    {
        myFrameBuffer.redFieldPosition = readUint8();
        myFrameBuffer.redMaskSize = readUint8();
        myFrameBuffer.greenFieldPosition =readUint8();
        myFrameBuffer.greenMaskSize = readUint8();
        myFrameBuffer.blueFieldPosition = readUint8();
        myFrameBuffer.blueMaskSize = readUint8();
        // Alignment padding
        readUint16();
        readUint8();
    }
    // Not direct display type
    else
    {
        // Alignment padding
        dataSize -= 22;
        myEbx = static_cast<uint8_t *>(myEbx) + dataSize;
    }
}

void BootInformation::readMemoryMap(const uint32_t dataSize)
{
    const uint8_t* root{static_cast<uint8_t*>(myEbx)};
    readUint32(); // Entry size (must be 24)
    readUint32(); // Entry version (must be 0)

    extern void* kernelStart;
    const uint64_t kernelStartAddress {reinterpret_cast<uint64_t>(&kernelStart)};

    extern void* kernelEnd;
    const uint64_t kernelEndAddress {reinterpret_cast<uint64_t>(&kernelEnd)};

    while (myEbx < root + dataSize)
    {
        uint64_t address {readUint64()};
        uint64_t size {readUint64()};
        uint32_t type {readUint32()};
        readUint32(); // Reserved, must be 0 and ignored
        // Ensures the entry is free ram
        if (type == 1 )
        {
            // Ensures that we don't overwrite the memory where the kernel is loaded.
            if (!(address + size > kernelStartAddress
                && kernelEndAddress > address))
            {
                myFreeMemory.pushBack({address, size});
            }
            // If a section of memory overlaps the kernel
            else
            {
                // Memory before the kernel
                if (address < kernelStartAddress)
                {
                    myFreeMemory.pushBack({address, kernelStartAddress - address});
                }
                // Memory after the kernel
                if (address + size > (kernelEndAddress + 1))
                {
                    myFreeMemory.pushBack({kernelEndAddress + 1, size + address - (kernelEndAddress + 1)});
                }
            }
        }
    }
}
