#include "DirectDisplay.hpp"

DirectDisplay::DirectDisplay(uint64_t address, uint32_t height, uint32_t width) : 
        myAddress{address},
        myHeight{height},
        myWidth{width}
{
}

void DirectDisplay::testDisplay()
{        
    uint16_t* pixel = (uint16_t*)myAddress;
    for (uint32_t iHeight{0}; iHeight < myHeight; iHeight++)
    {
        for (uint32_t iWidth{0}; iWidth < myWidth; iWidth++)
        {
            if (iWidth > myWidth/2 && iHeight > myHeight/2)
            {
                *pixel = 0xffff;
            }
            else 
            {
                *pixel = 0x0000;
            }
            pixel++;
        }
    }
}