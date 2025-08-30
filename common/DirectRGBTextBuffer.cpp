#include "DirectRGBTextBuffer.hpp"

DirectRGBTextBuffer::DirectRGBTextBuffer(const FrameBuffer& frameBuffer) :
    myFrameBuffer{frameBuffer},
    myMaxAddress{frameBuffer.address + (frameBuffer.pitch * frameBuffer.height)},
    myColumn{0},
    myRow{0}
{
    //TODO: Check bits per pixel, mask size
}

void DirectRGBTextBuffer::printChar(const uint32_t xPos, const uint32_t yPos, const char character)
{
    if (xPos >= myFrameBuffer.width/8 || yPos >= myFrameBuffer.height/16)
    {
        return;
    }

    Color color{0xff, 0xff, 0xff};

    uint32_t* currentAddress = reinterpret_cast<uint32_t *>(myFrameBuffer.address + (xPos * 8 * 4 + yPos * 16 * myFrameBuffer.pitch));

    // Font.S
    extern uint8_t fontGlyphs[];
    uint8_t* characterRow = &fontGlyphs[character * 16];

    for (uint8_t iGlyphPixel{0}; iGlyphPixel < 128; iGlyphPixel++)
    {
        if ((*characterRow >> (7 - iGlyphPixel % 8)) & 1)
        {
            uint32_t printColor = color.red << myFrameBuffer.redFieldPosition |
                color.green << myFrameBuffer.greenFieldPosition |
                color.blue << myFrameBuffer.blueFieldPosition;
            *currentAddress = printColor;
        }
        else
        {
            *currentAddress = 0x0;
        }
        currentAddress++;

        if ((iGlyphPixel + 1) % 8 == 0)
        {
            currentAddress = (uint32_t*)((uint8_t*)currentAddress + myFrameBuffer.pitch) - 8;
            characterRow++;
        }
    }
}


void DirectRGBTextBuffer::clearScreen()
{
    uint8_t* currentAddress = myFrameBuffer.address;
    while (currentAddress != myMaxAddress)
    {
        *currentAddress = 0x0;
        currentAddress++;
    }
    myColumn = 0;
    myRow = 0;
}

void DirectRGBTextBuffer::scrollText() const
{
    uint8_t* currentAddress = myFrameBuffer.address;
    while (currentAddress != (myMaxAddress - myFrameBuffer.pitch * 16))
    {
        *currentAddress = *(currentAddress + myFrameBuffer.pitch * 16);
        currentAddress++;
    }
    while (currentAddress != myMaxAddress)
    {
        *currentAddress = 0x0;
        currentAddress++;
    }
}

void DirectRGBTextBuffer::writeChar(const char character)
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

    if (myColumn >= myFrameBuffer.width/8)
    {
        myRow +=1;
        myColumn = 0;
    }
    if (myRow >= myFrameBuffer.height/16)
    {
        scrollText();
        myColumn = 0;
        myRow = myFrameBuffer.height/16 - 1;
    }
}