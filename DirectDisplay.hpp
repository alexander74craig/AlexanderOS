#pragma once

#include <stdint.h>

// 16 bit color depth display
class DirectDisplay
{
private:
    uint64_t myAddress;
    uint32_t myHeight;
    uint32_t myWidth;

public:

    DirectDisplay(uint64_t address, uint32_t height, uint32_t width);

    // Prints a pattern to test the display.
    void testDisplay();
};