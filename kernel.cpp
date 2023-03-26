extern "C"
{
#include <stdint.h>
#include "VGATextModeBuffer.hpp"
#include "BootInformation.hpp"

void main(uint32_t eax, void* ebx) 
{
    VGATextModeBuffer vgaBuffer;

    if (eax != 0x36d76289)
    {
        vgaBuffer.writeString("Invalid bootloader magic number.");
        return;
    }

    BootInformation bootInformation(ebx);
    if (bootInformation.valid ==  false)
    {
        vgaBuffer.writeString("Invalid boot information.\n");
        return;
    }

    vgaBuffer.writeString("frameBufferAddress: ");
    vgaBuffer.writeHexLong(bootInformation.framebufferAddress);
    vgaBuffer.writeString("\nframeBufferPitch ");
    vgaBuffer.writeHexWord(bootInformation.framebufferPitch);
    vgaBuffer.writeString("\nframeBufferWidth ");
    vgaBuffer.writeHexWord(bootInformation.framebufferWidth);
    vgaBuffer.writeString("\nframeBufferHeight ");
    vgaBuffer.writeHexWord(bootInformation.framebufferHeight);

    vgaBuffer.writeString("\nframeBufferBitsPerPixel ");
    vgaBuffer.writeHexByte(bootInformation.framebufferBitsPerPixel);
    vgaBuffer.writeString("\nframeBufferType ");
    vgaBuffer.writeHexByte(bootInformation.framebufferType);
    vgaBuffer.writeString("\nframeBufferRedFieldPosition ");
    vgaBuffer.writeHexByte(bootInformation.framebufferRedFieldPosition);
    vgaBuffer.writeString("\nframeBufferRedMaskSize ");
    vgaBuffer.writeHexByte(bootInformation.framebufferRedMaskSize);
    vgaBuffer.writeString("\nframeBufferGreenFieldPosition ");
    vgaBuffer.writeHexByte(bootInformation.framebufferGreenFieldPosition);
    vgaBuffer.writeString("\nframeBufferGreenMaskSize ");
    vgaBuffer.writeHexByte(bootInformation.framebufferGreenMaskSize);
    vgaBuffer.writeString("\nframeBufferBlueFieldPosition ");
    vgaBuffer.writeHexByte(bootInformation.framebufferBlueFieldPosition);
    vgaBuffer.writeString("\nframeBufferBlueMaskSize ");
    vgaBuffer.writeHexByte(bootInformation.framebufferBlueMaskSize);
    
    return;
}
}
