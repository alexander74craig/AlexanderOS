#include <stdint.h>

class VGATextModeBuffer
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

    void writeHexByte(uint8_t byte);

    void writeHexWord(uint16_t word);

    void writeHexLong(uint32_t longInt);

    // Writes a character at the current position and handles scrolling.
    void writeChar(char character);

    // Writes a string at the current position and handles scrolling.
    void writeString(char* string);

    // Clears the screen and sets current position to 0,0.
    void clearScreen();
};
