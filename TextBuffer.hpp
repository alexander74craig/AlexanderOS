#pragma once
#include <stdint.h>

class TextBuffer
{
public:
    virtual ~TextBuffer() = default;

    void writeHexNibble(uint8_t nibble);

    void writeHex(uint8_t byte);

    void writeHex(uint16_t int16);

    void writeHex(uint32_t int32);

    void writeHex(uint64_t int64);

    // Writes a character at the current position.
    virtual void writeChar(char character) = 0;

    // Writes a string at the current position.
    virtual void writeString(char* string);

    // Clears the screen and sets current character position to 0,0.
    virtual void clearScreen() = 0;
};