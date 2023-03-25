#include "BootInformation.hpp"
#include "VGATextModeBuffer.cpp"


BootInformation::BootInformation(void* ebx) : 
    valid{true}
{
    VGATextModeBuffer vgaBuffer;

    // Total size of boot information
    uint32_t total_size(readUint32(ebx));
    vgaBuffer.writeString("total Size ");
    vgaBuffer.writeHexWord(total_size);
    //Reserved 0s
    readUint32(ebx);

    uint32_t currentSize{8};
    while(currentSize < total_size)
    {
        // Tag type
        uint32_t type{readUint32(ebx)};

        // Size in bytes.
        uint32_t size{readUint32(ebx)};

        // Framebuffer Tag
        if (type == 8)
        {
            framebufferAddress = readUint64(ebx);
            framebufferPitch = readUint32(ebx);
            framebufferWidth = readUint32(ebx);
            framebufferHeight = readUint32(ebx);
            framebufferBitsPerPixel = readUint8(ebx);
            framebufferType = readUint8(ebx);
            // Reserved byte
            readUint8(ebx);

            if (framebufferType == 1)
            {
                framebufferRedFieldPosition = readUint8(ebx);
                framebufferRedMaskSize = readUint8(ebx);
                framebufferGreenFieldPosition =readUint8(ebx);
                framebufferGreenMaskSize = readUint8(ebx);
                framebufferBlueFieldPosition = readUint8(ebx);
                framebufferBlueMaskSize = readUint8(ebx);
                //Alignment padding
                readUint32(ebx);
            }
            else if (framebufferType == 0)
            {
                // Alignment padding
                uint32_t dataBytes = size - 22;
                if (dataBytes % 8 != 0)
                {
                    ebx = (uint8_t*)ebx + dataBytes + (8 - (dataBytes % 8));
                }
                else 
                {
                    ebx = (uint8_t*)ebx + dataBytes;
                }        
            }
            else
            {
                //Alignment padding
                framebufferRedFieldPosition = 0;
                framebufferRedMaskSize = 0;
                framebufferGreenFieldPosition = 0;
                framebufferGreenMaskSize = 0;
                framebufferBlueFieldPosition = 0;
                framebufferBlueMaskSize = 0;
                readUint16(ebx);
            }
        }
        else 
        {
            // Skips over the current data section
            // Increments of 8 bytes to account for padding.
            uint32_t dataBytes = size - 8;
            if (dataBytes % 8 != 0)
            {
               ebx = (uint8_t*)ebx + dataBytes + (8 - (dataBytes % 8));
            }
            else 
            {
                ebx = (uint8_t*)ebx + dataBytes;
            }
        }
        // Adds size plus padding to current size of data read.
        if (size % 8 != 0)
        {
            currentSize += size + (8 - (size % 8));
        }
        else 
        {
            currentSize += size;
        }
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
