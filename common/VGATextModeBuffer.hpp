#pragma once
#include "TextBuffer.hpp"

class VGATextModeBuffer : public TextBuffer
{
public:
    //! \brief Singleton constructor.
    //! \return Singleton instance of the vga text mode buffer.
    static VGATextModeBuffer& instance();

    //! \brief Deleted copy constructor.
    VGATextModeBuffer(const VGATextModeBuffer&) = delete;
    //! \brief Deleted copy assignment operator.
    VGATextModeBuffer& operator=(const VGATextModeBuffer&) = delete;
    //! \brief Deleted move constructor.
    VGATextModeBuffer(VGATextModeBuffer&&) = delete;
    //! \brief Deleted move assignment operator.
    VGATextModeBuffer& operator=(VGATextModeBuffer&&) = delete;

    //! \brief Defaulted destructor for polymorphism.
    ~VGATextModeBuffer() override = default;

    //! \brief Writes a character at the current position.
    //! \param[in] character Character to write.
    void writeChar(char character) override;

    //! \brief Clears the screen and sets the current position to 0,0.
    void clearScreen() override;

private:
    //! \brief Default constructor, clears the screen.
    VGATextModeBuffer();

    //! \brief Current horizontal character position. Max 80 characters per line
    uint32_t myColumn;
    //! \brief Current vertical line character position. Max 25 characters lines per screen
    uint32_t myRow;

    //! \brief Scrolls the screen one line, sets position to the first character of the last line.
    void scroll();
};
