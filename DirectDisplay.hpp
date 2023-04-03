#pragma once

#include <stdint.h>
#include "Color.hpp"
#include "BootInformation.hpp"

// 16 bit color depth display
class DirectDisplay
{
private:
    uint8_t* const myAddress;
    uint8_t* const myMaxAddress;

    const uint32_t myWidth;
    const uint32_t myHeight;
    const uint32_t myPitch;

    const uint8_t myRedFieldPosition;
    const uint8_t myRedMaskSize;
    const uint8_t myGreenFieldPosition;
    const uint8_t myGreenMaskSize;
    const uint8_t myBlueFieldPosition;
    const uint8_t myBlueMaskSize;

    // Current position on screen.
    uint32_t myColumn; 
    uint32_t myRow;

    void writeHexNibble(uint8_t nibble);

    void writeChar(const uint32_t xPos, const uint32_t yPos, char character, const Color color);

public:
    // Default constructor, clears the screen.
    DirectDisplay(BootInformation bootInformation);

    void writeHexByte(uint8_t byte);

    void writeHexWord(uint16_t word);

    void writeHexLong(uint32_t longInt);

    void writeHex64(uint64_t int64);

    // Writes a character at the current position and handles scrolling.
    void writeChar(char character);

    // Writes a string at the current position and handles scrolling.
    void writeString(char* string);

    // Clears the screen and sets current position to 0,0.
    void clearScreen();

    void scrollText();


};