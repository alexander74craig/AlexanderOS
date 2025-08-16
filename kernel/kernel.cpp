#include "stddef.h"

extern "C"
{

#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "VGATextModeBuffer.hpp"
#include "MemoryAllocator.hpp"

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

        for (uint32_t i = 0; i < bootInformation.numEntries; i++)
        {
            if (bootInformation.entries[i].type == 1)
            {
                textBuffer.writeString("\nbase address : ");
                textBuffer.writeHex(bootInformation.entries[i].baseAddress);
                textBuffer.writeString("  | length : ");
                textBuffer.writeHex(bootInformation.entries[i].length);
                textBuffer.writeString("  | type : ");
                textBuffer.writeHex(bootInformation.entries[i].type);
            }
        }
        const MemoryAllocator allocator(bootInformation, textBuffer);
        MemoryAllocatorNode* node = allocator.myRootAddress;
        if (node == nullptr)
        {
            textBuffer.writeString("\nMemory allocator empty.");
        }
        while (node != nullptr)
        {
            textBuffer.writeString("\n Address : ");
            textBuffer.writeHex(reinterpret_cast<uint64_t>(node));
            textBuffer.writeString("  | length : ");
            textBuffer.writeHex(node->length);
            node = node->nextAddress;
        }
    }
}
}
