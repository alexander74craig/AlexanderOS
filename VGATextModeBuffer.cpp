#include "VGATextModeBuffer.hpp"

VGATextModeBuffer::VGATextModeBuffer() :
        myColumn{0},
        myRow{0}
{
}

void VGATextModeBuffer::scroll()
{
    char* position = (char*) 0xB8000;
    char* nextLinePos = position + 160;
    for (uint32_t myRow{0}; myRow < 24; myRow++)
    {
        for (uint32_t myColumn{0}; myColumn < 80; myColumn++)
        {
            *position =*nextLinePos;
            position +=2;
            nextLinePos +=2;
        }
    }
    for (uint32_t myColumn{0}; myColumn < 80; myColumn++)
    {
        *position = ' ';
        position +=2;
    }
}

void VGATextModeBuffer::writeHexNibble(uint8_t nibble)
{
    if (nibble < 10)   
    {
        writeChar(nibble + 48);
    }
    else if (nibble < 16)
    {
        writeChar(nibble + 55);
    }
    else 
    {
        writeChar('?');
    }
}

void VGATextModeBuffer::writeHexByte(uint8_t byte)
{
    uint8_t lower = 0xF & byte;
    uint8_t upper = byte >> 4;
    writeHexNibble(upper);
    writeHexNibble(lower);
}

void VGATextModeBuffer::writeHexWord(uint16_t word)
{
    uint8_t lower = 0xFF & word;
    uint8_t upper = word >> 8;
    writeHexByte(upper);
    writeHexByte(lower);
}

void VGATextModeBuffer::writeHexLong(uint32_t longInt)
{
    uint16_t lower = 0xFFFF & longInt;
    uint16_t upper = longInt >> 16;
    writeHexWord(upper);
    writeHexWord(lower);
}

void VGATextModeBuffer::writeChar(char character)
{
    if (character == '\n')
    {            
        myRow +=1;
        myColumn = 0;
    }
    else 
    {
        char* position = (char*) 0xB8000;
        position += (myColumn * 2) + (myRow * 160);
        *position = character;
        myColumn++;
    }

    if (myColumn > 79)
    {
        myRow +=1;
        myColumn = 0;
    }
    if (myRow > 24)
    {
        scroll();
        myColumn = 0;
        myRow = 24;
    }
}

void VGATextModeBuffer:: writeString(char* string)
{
    for (uint32_t charIndex{0}; string[charIndex]; charIndex++)
    {
        writeChar(string[charIndex]);
    }
}

void VGATextModeBuffer::clearScreen()
{
    char* position = (char*) 0xB8000;
    for (uint32_t myRow{0}; myRow < 25; myRow++)
    {
        for (uint32_t myColumn{0}; myColumn < 80; myColumn++)
        {
            *position = ' ';
            position +=2;
        }
    }
    myColumn = 0;
    myRow = 0;
}
