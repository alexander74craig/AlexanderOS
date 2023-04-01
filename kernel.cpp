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
    
    DirectDisplay display(bootInformation.framebufferAddress, bootInformation.framebufferWidth, bootInformation.framebufferHeight);
    
    display.writeString("Alexander OS!\n");
    display.writeString("1234567890-=\n");
    display.writeString("!@#$%^&*()_+\n");
    display.writeString("[]\\;',./{}|:\">?~`\n");
    display.writeString("the quick brown fox jumps over the lazy dog.\n");
    display.writeString("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG!\n");
    return;
}
}
