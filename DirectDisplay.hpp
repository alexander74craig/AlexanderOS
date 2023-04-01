#pragma once

#include <stdint.h>

// 16 bit color depth display
class DirectDisplay
{
private:
    uint32_t* const myAddress;
    const uint32_t myHeight;
    const uint32_t myWidth;
    uint32_t* const myMaxAddress;

    // Current position on screen.
    uint32_t myColumn; 
    uint32_t myRow;

    void writeHexNibble(uint8_t nibble);

    void writeChar(uint32_t xPos, uint32_t yPos, char character);

public:
    // Default constructor, clears the screen.
    DirectDisplay(uint64_t address,  uint32_t width, uint32_t height);

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