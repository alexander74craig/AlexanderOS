#include "DirectDisplay.hpp"

DirectDisplay::DirectDisplay(uint64_t address, uint32_t height, uint32_t width) : 
        myAddress{(uint16_t*)address},
        myHeight{height},
        myWidth{width},
        myMaxAddress{(uint16_t*)myAddress + (myWidth * myHeight)}
{
}


void DirectDisplay::printChar(uint32_t xPos, uint32_t yPos, char character)
{
    if (xPos >= 80 || yPos >=30)
    {
        return;
    }
 
    uint16_t* currentAddress = myAddress + (xPos * 8 + yPos * 16 * myWidth);
    uint8_t* characterRow = myFont.getGlyph(character);

    for (uint8_t iGlyphPixel{0}; iGlyphPixel < 128; iGlyphPixel++)
    {
        if ((*characterRow >> (7 - iGlyphPixel % 8)) & 1)
        {
            *currentAddress = 0xffff;
        }
        else
        {
            *currentAddress = 0x0;
        }
        currentAddress++;

        if ((iGlyphPixel + 1) % 8 == 0)
        {
            currentAddress += myWidth - 8;
            characterRow++;
        }
    }
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