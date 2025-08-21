#pragma once

#include "stddef.h"
#include "TextBuffer.hpp"
#include "Color.hpp"
#include "BootInformation.hpp"

//! \brief 16 bit color depth display
class DirectDisplayTextBuffer : public TextBuffer
{
public:
    //! \brief Default constructor, clears the screen.
    //! \param[in] frameBuffer Framebuffer information used to display
    explicit DirectDisplayTextBuffer(const FrameBuffer& frameBuffer);

    //! \brief Defaulted destructor for polymorphism.
    ~DirectDisplayTextBuffer() override = default;

    //! \brief Writes a character at the current position and handles scrolling.
    //! \param[in] character Character to write.
    void writeChar(char character) override;

    //! \brief Clears the screen and sets current position to 0,0.
    void clearScreen() override;

private:
    //! \brief Writes a character to the given position on the screen.
    //! \param[in] xPos Character horizontal position within a line. If invalid, aborts write.
    //! \param[in] yPos Character vertical line position. If invalid, aborts write.
    //! \param[in] character Character to write.
    void printChar(uint32_t xPos, uint32_t yPos, char character);

    //! \brief Moves all text up one line, leaving the bottom line clear.
    void scrollText() const;

    //! \brief Framebuffer information.
    const FrameBuffer myFrameBuffer;

    //! \brief Address just beyond the end of the framebuffer
    const uint8_t* const myMaxAddress;

    //! \brief Current horizontal character position on screen.
    uint32_t myColumn;

    //! \brief Current vertical character position on screen.
    uint32_t myRow;

};