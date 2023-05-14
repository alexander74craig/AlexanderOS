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

        for (uint32_t memoryMapEntryIndex{0}; memoryMapEntryIndex < 32; memoryMapEntryIndex++)
        {
            auto* mapEntry = bootInformation.memoryMapEntries + memoryMapEntryIndex;
            if(mapEntry->length == 0)
            {
                break;
            }
            textBuffer.writeString("\nAddress: ");
            textBuffer.writeHex(mapEntry->baseAddress);
            textBuffer.writeString(" ; Length: ");
            textBuffer.writeHex(mapEntry->length);
            textBuffer.writeString(" ; Type: ");
            textBuffer.writeHex(mapEntry->type);
        }
        PhysicalMemoryManager physicalMemoryManager(bootInformation);
    }
}
}
