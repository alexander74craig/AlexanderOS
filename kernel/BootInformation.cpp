#include "BootInformation.hpp"

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
    framebufferAddress = readUint64();
    framebufferPitch = readUint32();
    framebufferWidth = readUint32();
    framebufferHeight = readUint32();
    framebufferBitsPerPixel = readUint8();
    framebufferType = readUint8();
    // Reserved 2 bytes
    readUint16();
    // Direct Display type
    if (framebufferType == 1)
    {
        framebufferRedFieldPosition = readUint8();
        framebufferRedMaskSize = readUint8();
        framebufferGreenFieldPosition =readUint8();
        framebufferGreenMaskSize = readUint8();
        framebufferBlueFieldPosition = readUint8();
        framebufferBlueMaskSize = readUint8();
        // Alignment padding
        readUint16();
        readUint8();
    }
        // Not direct display type
    else
    {
        framebufferRedFieldPosition = 0;
        framebufferRedMaskSize = 0;
        framebufferGreenFieldPosition = 0;
        framebufferGreenMaskSize = 0;
        framebufferBlueFieldPosition = 0;
        framebufferBlueMaskSize = 0;
        // Alignment padding
        dataSize -= 22;
        myEbx = static_cast<uint8_t *>(myEbx) + dataSize;
    }
}

void BootInformation::readMemoryMap(const uint32_t dataSize)
{
    const uint8_t* root{static_cast<uint8_t*>(myEbx)};
    hasMemoryMap = true;
    readUint32(); // Entry size (must be 24)
    readUint32(); // Entry version (must be 0)
    while (myEbx < root + dataSize)
    {
        entries[numEntries].baseAddress = readUint64();
        entries[numEntries].length = readUint64();
        entries[numEntries].type = readUint32();
        entries[numEntries].reserved = readUint32();
        numEntries++;
    }
}