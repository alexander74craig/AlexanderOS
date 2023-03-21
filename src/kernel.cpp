extern "C"
{
#include <stdint.h>
#include "VGATextModeBuffer.cpp"

uint32_t readBootTag(uint32_t*& address, VGATextModeBuffer& vgaBuffer)
{
    vgaBuffer.writeString("type = ");
    vgaBuffer.writeHexLong(*address);
    uint32_t type{*address};
    address++;

    vgaBuffer.writeString("| size = ");
    vgaBuffer.writeHexLong(*address);
    uint32_t size = *address;
    address++;

    vgaBuffer.writeString("| data: ");
    uint32_t currentSize{8};

    if (type != 9)
    {
        while (currentSize < size)
        {
            vgaBuffer.writeHexLong(*address);
            address++;
            vgaBuffer.writeChar(' ');

            vgaBuffer.writeHexLong(*address);
            address++;
            vgaBuffer.writeChar(' ');
            currentSize += 8;
        } 
    }
    else 
    {
        vgaBuffer.writeString("Skipped.");
        while (currentSize < size)
        {
            address++;
            address++;
            currentSize += 8;
        } 
    }
    
    vgaBuffer.writeChar('\n');
    return currentSize;
}


void main(uint32_t eax, uint32_t* ebx) 
{
    VGATextModeBuffer vgaBuffer;

    if (eax != 0x36d76289)
    {
        vgaBuffer.writeString("Invalid bootloader magic number.");
        return;
    }

    vgaBuffer.writeString("total_size = ");
    vgaBuffer.writeHexLong(*ebx);
    vgaBuffer.writeChar('\n');
    uint32_t total_size{*ebx};
    ebx++;

    //Reserved 0s
    ebx++;

    uint32_t currentSize{8};
    while(currentSize < total_size)
    {
        currentSize += readBootTag(ebx, vgaBuffer);
    }

    return;
}
}
