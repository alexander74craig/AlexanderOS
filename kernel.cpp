extern "C"
{
#include <stdint.h>
#include "BootInformation.hpp"
#include "DirectDisplay.hpp"
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
        textBuffer.writeString("VGA text buffer");
    }
    else if (bootInformation.framebufferType == 1)
    {
        DirectDisplay textBuffer{bootInformation};
        textBuffer.writeString("Direct display text buffer.\n");
        if (bootInformation.hasBasicsMemoryInformation)
        {
            textBuffer.writeString("Memory upper address :");
            textBuffer.writeHex(bootInformation.memoryLowerAddress);
            textBuffer.writeString("\nMemory lower address :");
            textBuffer.writeHex(bootInformation.memoryUpperAddress);
        }
        else
        {
            textBuffer.writeString("Has no basic memory information.");
            return;
        }
    }  

}
}
