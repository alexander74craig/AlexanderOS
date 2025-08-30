#pragma once

#include "stdint.h"

class TextBuffer
{
public:
    virtual ~TextBuffer() = default;

    void write(uint8_t byte);

    void write(uint16_t int16);

    void write(uint32_t int32);

    void write(uint64_t int64);

    // Writes a string at the current position.
    void write(const char* string);

    void write(bool boolean);

private:
    // Writes a character at the current position.
    virtual void writeChar(char character) = 0;

    void writeHexNibble(uint8_t nibble);
};