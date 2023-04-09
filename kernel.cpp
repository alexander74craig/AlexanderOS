extern "C"
{
#include <stdint.h>
#include "BootInformation.hpp"
#include "DirectDisplay.hpp"

void main(uint32_t cpuidFeaturesEDX, uint32_t cpuidFeaturesECX, uint32_t grubMagicNumber, void* grubBootInformationAddress) 
{

    if (grubMagicNumber != 0x36d76289)
    {
        //TODO: Invalid bootloader magic number.
        return;
    }
    BootInformation bootInformation(grubBootInformationAddress);
    DirectDisplay display(bootInformation);
    

    display.writeHexLong(cpuidFeaturesECX);
    display.writeString(" - cpuid features ECX \n");
    display.writeHexLong(cpuidFeaturesEDX);
    display.writeString(" - cpuid features EDX \n");
    (cpuidFeaturesEDX & 0x200) ? display.writeString("Has APIC\n") : display.writeString("Does not have APIC\n");
}
}
