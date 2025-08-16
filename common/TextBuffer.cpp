#include "TextBuffer.hpp"

void TextBuffer::writeHexNibble(uint8_t nibble)
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

void TextBuffer::writeHex(uint8_t byte)
{
    uint8_t lower = 0xF & byte;
    uint8_t upper = byte >> 4;
    writeHexNibble(upper);
    writeHexNibble(lower);
}

void TextBuffer::writeHex(const uint16_t int16)
{
    const uint8_t lower = 0xFF & int16;
    const uint8_t upper = int16 >> 8;
    writeHex(upper);
    writeHex(lower);
}

void TextBuffer::writeHex(const uint32_t int32)
{
    const uint16_t lower = 0xFFFF & int32;
    const uint16_t upper = int32 >> 16;
    writeHex(upper);
    writeHex(lower);
}

void TextBuffer::writeHex(uint64_t int64)
{
    const uint32_t lower = 0xFFFFFFFF & int64;
    const uint32_t upper = int64 >> 32;
    writeHex(upper);
    writeHex(lower);
}

void TextBuffer:: writeString(char* string)
{
    for (uint32_t charIndex{0}; string[charIndex]; charIndex++)
    {
        writeChar(string[charIndex]);
    }
}
