#include "DirectDisplay.hpp"

DirectDisplay::DirectDisplay(BootInformation bootInformation) : 
    myWidth{bootInformation.framebufferWidth},
    myHeight{bootInformation.framebufferHeight},
    myPitch{bootInformation.framebufferPitch},
    myRedFieldPosition{bootInformation.framebufferRedFieldPosition},
    myRedMaskSize{bootInformation.framebufferRedMaskSize},
    myGreenFieldPosition{bootInformation.framebufferGreenFieldPosition},
    myGreenMaskSize{bootInformation.framebufferGreenMaskSize},
    myBlueFieldPosition{bootInformation.framebufferBlueFieldPosition},
    myBlueMaskSize{bootInformation.framebufferBlueMaskSize},
    myAddress{(uint8_t*)bootInformation.framebufferAddress},
    myMaxAddress{myAddress + (myPitch * myHeight)},
    myColumn{0},
    myRow{0}
{
    //TODO: Check bits per pixel, mask size, and 
    clearScreen();
}

void DirectDisplay::printChar(uint32_t xPos, uint32_t yPos, char character)
{
    if (xPos >= myWidth/8 || yPos >= myHeight/16)
    {
        return;
    }

    Color color{0xff, 0xff, 0xff};

    uint32_t* currentAddress = (uint32_t*)(myAddress + (xPos * 8 * 4 + yPos * 16 * myPitch));

    // Font.s
    extern uint8_t fontGlyphs[];
    uint8_t* characterRow = &fontGlyphs[character * 16];

    for (uint8_t iGlyphPixel{0}; iGlyphPixel < 128; iGlyphPixel++)
    {
        if ((*characterRow >> (7 - iGlyphPixel % 8)) & 1)
        {
            uint32_t printColor = color.red << myRedFieldPosition | 
                color.green << myGreenFieldPosition | 
                color.blue << myBlueFieldPosition;
            *currentAddress = printColor;
        }
        else
        {
            *currentAddress = 0x0;
        }
        currentAddress++;

        if ((iGlyphPixel + 1) % 8 == 0)
        {
            currentAddress = (uint32_t*)((uint8_t*)currentAddress + myPitch) - 8;
            characterRow++;
        }
    }
}


void DirectDisplay::clearScreen()
{
    uint8_t* currentAddress = myAddress;
    while (currentAddress != myMaxAddress)
    {
        *currentAddress = 0x0;
        currentAddress++;
    }
    myColumn = 0;
    myRow = 0;
}

void DirectDisplay::scrollText()
{
    uint8_t* currentAddress = myAddress;
    while (currentAddress != (myMaxAddress - myPitch * 16))
    {
        *currentAddress = *(currentAddress + myPitch * 16);
        currentAddress++;
    }
    while (currentAddress != myMaxAddress)
    {
        *currentAddress = 0x0;
        currentAddress++;
    }
}

void DirectDisplay::writeChar(char character)
{
    if (character == '\n')
    {            
        myRow +=1;
        myColumn = 0;
    }
    else 
    {
        printChar(myColumn, myRow, character);
        myColumn++;
    }

    if (myColumn >= myWidth/8)
    {
        myRow +=1;
        myColumn = 0;
    }
    if (myRow >= myHeight/16)
    {
        scrollText();
        myColumn = 0;
        myRow = myHeight/16 - 1;
    }
}