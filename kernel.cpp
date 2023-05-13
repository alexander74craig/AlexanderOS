extern "C"
{
#include <stdint.h>
#include "BootInformation.hpp"
#include "DirectDisplay.hpp"
#include "VGATextModeBuffer.hpp"
#include "PhysicalMemoryManager.hpp"

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
        DirectDisplay textBuffer{bootInformation};
        textBuffer.writeString("Direct display text buffer.");
        PhysicalMemoryManager physicalMemoryManager(bootInformation, textBuffer);
        uint8_t* address = (uint8_t*)physicalMemoryManager.allocateAddress();
        textBuffer.writeString("\nAddress allocated by the PMM: ");
        textBuffer.writeHex((uint32_t) address);
        uint8_t* address2 = (uint8_t*)physicalMemoryManager.allocateAddress();
        textBuffer.writeString("\nAddress2 allocated by the PMM: ");
        textBuffer.writeHex((uint32_t) address2);
    }
}
}
