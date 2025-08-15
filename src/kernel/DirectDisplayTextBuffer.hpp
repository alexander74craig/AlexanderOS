#pragma once

#include "StandardDefinitions.hpp"
#include "TextBuffer.hpp"
#include "Color.hpp"
#include "BootInformation.hpp"

// 16 bit color depth display
class DirectDisplayTextBuffer : public TextBuffer
{
private:
    uint8_t* const myAddress;
    const uint32_t myWidth;
    const uint32_t myHeight;
    const uint32_t myPitch;
    uint8_t* const myMaxAddress;

    const uint8_t myRedFieldPosition;
    const uint8_t myRedMaskSize;
    const uint8_t myGreenFieldPosition;
    const uint8_t myGreenMaskSize;
    const uint8_t myBlueFieldPosition;
    const uint8_t myBlueMaskSize;

    // Current position on screen.
    uint32_t myColumn; 
    uint32_t myRow;

    void printChar(uint32_t xPos, uint32_t yPos, char character);

    void scrollText() const;
    
public:
    // Default constructor, clears the screen.
    explicit DirectDisplayTextBuffer(const BootInformation& bootInformation);

    ~DirectDisplayTextBuffer() override = default;

    // Writes a character at the current position and handles scrolling.
    void writeChar(char character) override;

    // Clears the screen and sets current position to 0,0.
    void clearScreen() override;
};