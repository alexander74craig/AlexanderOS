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

    


    //display.testDisplay();
    
    char character = 0x0;
    for (uint32_t iHeight{0}; iHeight < 30; iHeight++)
    {
        for (uint32_t iWidth{0}; iWidth < 80; iWidth++)
        {
            display.printChar(iWidth, iHeight, character);
            character++;
        }
    }
    
    return;
}
}
