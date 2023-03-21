#include <stdint.h>

class VGATextModeBuffer
{
private:
    // Current position on screen.
    uint32_t column = 0; // Max 80 characters per line
    uint32_t row = 0; // Max 25 characters lines per screen

    // Scrolls the screen one line, sets position to the first character of the last line.
    void scroll()
    {
        char* position = (char*) 0xB8000;
        char* nextLinePos = position + 160;
        for (uint32_t row{0}; row < 24; row++)
        {
            for (uint32_t column{0}; column < 80; column++)
            {
                *position =*nextLinePos;
                position +=2;
                nextLinePos +=2;
            }
        }
        for (uint32_t column{0}; column < 80; column++)
        {
            *position = ' ';
            position +=2;
        }
    }

    void writeHexNibble(uint8_t nibble)
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

public:
    // Default constructor, clears the screen.
    VGATextModeBuffer() = default;

    void writeHexByte(uint8_t byte)
    {
        uint8_t lower = 0xF & byte;
        uint8_t upper = byte >> 4;
        writeHexNibble(upper);
        writeHexNibble(lower);
    }

    void writeHexWord(uint16_t word)
    {
        uint8_t lower = 0xFF & word;
        uint8_t upper = word >> 8;
        writeHexByte(upper);
        writeHexByte(lower);
    }

    void writeHexLong(uint32_t longInt)
    {
        uint16_t lower = 0xFFFF & longInt;
        uint16_t upper = longInt >> 16;
        writeHexWord(upper);
        writeHexWord(lower);
    }

    // Writes a character at the current position and handles scrolling.
    void writeChar(char character)
    {
        if (character == '\n')
        {            
            row +=1;
            column = 0;
        }
        else 
        {
            char* position = (char*) 0xB8000;
            position += (column * 2) + (row * 160);
            *position = character;
            column++;
        }

        if (column > 79)
        {
            row +=1;
            column = 0;
        }
        if (row > 24)
        {
            scroll();
            column = 0;
            row = 24;
        }
    }

    // Writes a string at the current position and handles scrolling.
    void writeString(char* string)
    {
        for (uint32_t charIndex{0}; string[charIndex]; charIndex++)
        {
            writeChar(string[charIndex]);
        }
    }

    // Clears the screen and sets current position to 0,0.
    void clearScreen()
    {
        char* position = (char*) 0xB8000;
        for (uint32_t row{0}; row < 25; row++)
        {
            for (uint32_t column{0}; column < 80; column++)
            {
                *position = ' ';
                position +=2;
            }
        }
        column = 0;
        row = 0;
    }
};
