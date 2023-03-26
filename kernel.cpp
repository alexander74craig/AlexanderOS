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

    DirectDisplay display(bootInformation.framebufferAddress, 
            bootInformation.framebufferHeight, 
            bootInformation.framebufferWidth);

    display.testDisplay();
    
    return;
}
}
