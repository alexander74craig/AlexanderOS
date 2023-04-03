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


#define White Color{0xff, 0xff, 0xff} 

void DirectDisplay::writeChar(uint32_t xPos, uint32_t yPos, char character, Color color = Color(0xff, 0xff, 0xff))
{
    if (xPos >= myWidth/8 || yPos >= myHeight/16)
    {
        return;
    }

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

void DirectDisplay::writeHexNibble(uint8_t nibble)
{
    if (nibble < 10)   
    {
        writeChar(nibble + 48);
    }
    else
    {
        writeChar(nibble + 55);
    }
}

void DirectDisplay::writeHexByte(uint8_t byte)
{
    uint8_t lower = 0xF & byte;
    uint8_t upper = byte >> 4;
    writeHexNibble(upper);
    writeHexNibble(lower);
}

void DirectDisplay::writeHexWord(uint16_t word)
{
    uint8_t lower = 0xFF & word;
    uint8_t upper = word >> 8;
    writeHexByte(upper);
    writeHexByte(lower);
}

void DirectDisplay::writeHexLong(uint32_t longInt)
{
    uint16_t lower = 0xFFFF & longInt;
    uint16_t upper = longInt >> 16;
    writeHexWord(upper);
    writeHexWord(lower);
}

void DirectDisplay::writeHex64(uint64_t int64)
{
    uint32_t lower = 0xFFFFFFFF & int64;
    uint32_t upper = int64 >> 32;
    writeHexLong(upper);
    writeHexLong(lower);
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
        writeChar(myColumn, myRow, character);
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

void DirectDisplay:: writeString(char* string)
{
    for (uint32_t charIndex{0}; string[charIndex]; charIndex++)
    {
        writeChar(string[charIndex]);
    }
}