#pragma once

#include <stdint.h>
#include "Font.hpp"

// 16 bit color depth display
class DirectDisplay
{
private:
    uint16_t* const myAddress;
    const uint32_t myHeight;
    const uint32_t myWidth;
    uint16_t* const myMaxAddress;
    Font myFont;


public:

    DirectDisplay(uint64_t address, uint32_t height, uint32_t width);

    void printChar(uint32_t xPos, uint32_t yPos, char character);

    // Prints a pattern to test the display.
    void testDisplay();
};