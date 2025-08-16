#pragma once
#include "stddef.h"
#include "TextBuffer.hpp"

class VGATextModeBuffer : public TextBuffer
{
private:
    // Current position on screen.
    uint32_t myColumn; // Max 80 characters per line
    uint32_t myRow; // Max 25 characters lines per screen

    // Scrolls the screen one line, sets position to the first character of the last line.
    void scroll();

    void writeHexNibble(uint8_t nibble);

public:
    // Default constructor, clears the screen.
    VGATextModeBuffer();

    ~VGATextModeBuffer() override = default;

    // Writes a character at the current position.
    void writeChar(char character) override;

    // Clears the screen and sets current position to 0,0.
    void clearScreen() override;
};
