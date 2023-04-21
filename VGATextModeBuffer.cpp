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
