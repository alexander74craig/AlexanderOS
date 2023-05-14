#include "BootInformation.hpp"

BootInformation::BootInformation(void* ebx)
{
    // Total size of boot information
    uint32_t total_size(readUint32(ebx));
    //Reserved 0s
    readUint32(ebx);

    uint32_t currentSize{8};
    while(currentSize < total_size)
    {
        // Tag type
        uint32_t type{readUint32(ebx)};

        // Size in bytes.
        uint32_t size{readUint32(ebx)};

        uint32_t dataSize = size - 8;
        // Checks for padding to maintain tag alignment
        if (dataSize % 8 != 0)
        {
            dataSize = dataSize + (8 - (dataSize % 8));
        }
        if (type == 8)
        {
            readFramebuffer(ebx, dataSize);
        }
        else if (type == 4)
        {
            readBasicMemoryInformation(ebx);
        }
        else if (type == 6)
        {
            readMemoryMap(ebx, dataSize);
        }
        else 
        {
            // Skips over the current data section
            ebx = (uint8_t*)ebx + dataSize;
        }
        // Adds size plus padding to current size of data read.
        currentSize += dataSize + 8;
    }
}



uint64_t BootInformation::readUint64(void*& ebx)
{
    uint64_t returnInt{*(uint64_t*)ebx};
    ebx = (uint64_t*)ebx + 1;
    return returnInt;
}
uint32_t BootInformation::readUint32(void*& ebx)
{
    uint32_t returnInt{*(uint32_t*)ebx};
    ebx = (uint32_t*)ebx + 1;
    return returnInt;
}
uint16_t BootInformation::readUint16(void*& ebx)
{
    uint16_t returnInt{*(uint16_t*)ebx};
    ebx = (uint16_t*)ebx + 1;
    return returnInt;
}
uint8_t BootInformation::readUint8(void*& ebx)
{
    uint8_t returnInt{*(uint8_t*)ebx};
    ebx = (uint8_t*)ebx + 1;
    return returnInt;
}

void BootInformation::readFramebuffer(void*& ebx, uint32_t dataSize)
{
    framebufferAddress = readUint64(ebx);
    framebufferPitch = readUint32(ebx);
    framebufferWidth = readUint32(ebx);
    framebufferHeight = readUint32(ebx);
    framebufferBitsPerPixel = readUint8(ebx);
    framebufferType = readUint8(ebx);
    // Reserved 2 bytes
    readUint16(ebx);
    // Direct Display type
    if (framebufferType == 1)
    {
        framebufferRedFieldPosition = readUint8(ebx);
        framebufferRedMaskSize = readUint8(ebx);
        framebufferGreenFieldPosition =readUint8(ebx);
        framebufferGreenMaskSize = readUint8(ebx);
        framebufferBlueFieldPosition = readUint8(ebx);
        framebufferBlueMaskSize = readUint8(ebx);
        // Alignment padding
        readUint16(ebx);
        readUint8(ebx);
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
        ebx = (uint8_t*)ebx + dataSize;
    }
}

void BootInformation::readBasicMemoryInformation(void*& ebx)
{
    hasBasicsMemoryInformation = true;
    memoryLower = readUint32(ebx);
    memoryUpper = readUint32(ebx);
}
void BootInformation::readMemoryMap(void*& ebx,  uint32_t dataSize)
{
    //Entry size presumed to be 24
    readUint32(ebx);
    // Entry version presumed to be 0
    readUint32(ebx);

    uint32_t entriesSize{dataSize - 8};
    for (uint32_t entryIndex{0}; entryIndex < entriesSize/24; entryIndex++)
    {
        MemoryMapEntry* entry = memoryMapEntries + entryIndex;
        entry->baseAddress = readUint64(ebx);
        entry->length = readUint64(ebx);
        entry->type = readUint32(ebx);
        readUint32(ebx); // Reserved
    }

}