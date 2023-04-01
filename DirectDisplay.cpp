#include "DirectDisplay.hpp"

DirectDisplay::DirectDisplay(uint64_t address, uint32_t width, uint32_t height) : 
        myAddress{(uint32_t*)address},
        myHeight{height},
        myWidth{width},
        myMaxAddress{(uint32_t*)myAddress + (myWidth * myHeight)},
        myColumn{0},
        myRow{0}
{
    clearScreen();
}

#pragma pack(push, 1)
struct pixelColor
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    
};
#pragma pack(pop)

void DirectDisplay::writeChar(uint32_t xPos, uint32_t yPos, char character)
{
    if (xPos >= myWidth/8 || yPos >= myHeight/16)
    {
        return;
    }
 
    uint32_t* currentAddress = myAddress + (xPos * 8 + yPos * 16 * myWidth);
    // Font.s
    extern uint8_t fontGlyphs[];
    uint8_t* characterRow = &fontGlyphs[character * 16];

    for (uint8_t iGlyphPixel{0}; iGlyphPixel < 128; iGlyphPixel++)
    {
        if ((*characterRow >> (7 - iGlyphPixel % 8)) & 1)
        {
            *currentAddress = 0xffffffff;
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


void DirectDisplay::clearScreen()
{
    uint32_t* currentAddress = myAddress;
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
    uint32_t* currentAddress = myAddress;
    while (currentAddress != (myMaxAddress - myWidth * 8))
    {
        *currentAddress = *(currentAddress + myWidth * 8);
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
