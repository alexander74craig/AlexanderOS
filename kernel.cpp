extern "C"
{
#include <stdint.h>
#include "BootInformation.hpp"
#include "DirectDisplay.hpp"

void main(uint32_t eax, void* ebx) 
{

    if (eax != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }

    BootInformation bootInformation(ebx);
    
    DirectDisplay display(bootInformation);
    
    display.writeHex64(bootInformation.framebufferAddress);
    display.writeString(" - address \n");
    display.writeHexLong(bootInformation.framebufferWidth);
    display.writeString(" - width \n");
    display.writeHexLong(bootInformation.framebufferHeight);
    display.writeString(" - height \n");
    display.writeHexByte(bootInformation.framebufferBitsPerPixel);
    display.writeString(" - BPP \n");

    display.writeHexByte(bootInformation.framebufferType);
    display.writeString(" - type \n");

    display.writeHexByte(bootInformation.framebufferRedFieldPosition);
    display.writeString(" - RedFieldPosition \n");
    display.writeHexByte(bootInformation.framebufferGreenFieldPosition);
    display.writeString(" - GreenFieldPosition \n");
    display.writeHexByte(bootInformation.framebufferBlueFieldPosition);
    display.writeString(" - BlueFieldPosition \n");

    display.writeHexByte(bootInformation.framebufferRedMaskSize);
    display.writeString(" - RedMaskSize \n");
    display.writeHexByte(bootInformation.framebufferGreenMaskSize);
    display.writeString(" - GreenMaskSize \n");
    display.writeHexByte(bootInformation.framebufferBlueMaskSize);
    display.writeString(" - BlueMaskSize \n");
    return;
}
}
