extern "C"
{
#include <stdint.h>
#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "VGATextModeBuffer.hpp"

void main(uint32_t cpuidFeaturesEDX, uint32_t cpuidFeaturesECX, uint32_t grubMagicNumber, void* grubBootInformationAddress) 
{

    if (grubMagicNumber != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }

    BootInformation bootInformation(grubBootInformationAddress);

    if (bootInformation.framebufferType == 2)
    {
        VGATextModeBuffer textBuffer{};
        textBuffer.writeString("VGA text buffer.");
    }
    else if (bootInformation.framebufferType == 1)
    {
        DirectDisplayTextBuffer textBuffer{bootInformation};
        textBuffer.writeString("Direct display text buffer.\n");

        textBuffer.writeString("\nnum entries : ");
        textBuffer.writeHex(bootInformation.numEntries);

        for (int i = 0; i < bootInformation.numEntries; i++)
        {
            textBuffer.writeString("\nbase address : ");
            textBuffer.writeHex(bootInformation.entries[i].baseAddress);
            textBuffer.writeString("  | length : ");
            textBuffer.writeHex(bootInformation.entries[i].length);
            textBuffer.writeString("  | type : ");
            textBuffer.writeHex(bootInformation.entries[i].type);
            textBuffer.writeString("  | reserved : ");
            textBuffer.writeHex(bootInformation.entries[i].reserved);
        }
    }
}
}
