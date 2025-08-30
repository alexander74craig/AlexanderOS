#pragma once

#include "stdint.h"

enum class FrameBufferType
{
    Palette = 0,
    Direct = 1,
    EGA = 2
};

//! \brief Stores information about the frame buffer.
struct FrameBuffer
{
    //! \brief Address of frame buffer.
    uint8_t* address{nullptr};
    //! \brief Bytes per line. IE width * Bits per pixel
    uint32_t pitch{0};
    //! \brief Width in pixels, or characters if framebufferType = 2
    uint32_t width{0};
    //! \brief Height in pixels, or characters if framebufferType = 2
    uint32_t height{0};
    //! \brief Bits per pixel
    uint8_t bitsPerPixel{0};
    //! Frame buffer type 0 = Indexed color, 1 = direct RGB, 2 = EGA Text
    FrameBufferType type{};
    //! \brief Position of the red color bits
    uint8_t redFieldPosition{0};
    //! \brief Size, in bits, of the red color
    uint8_t redMaskSize{0};
    //! \brief Position of the green color bits
    uint8_t greenFieldPosition{0};
    //! \brief Size, in bits, of the green color
    uint8_t greenMaskSize{0};
    //! \brief Position of the blue color bits
    uint8_t blueFieldPosition{0};
    //! \brief Size, in bits, of the blue color
    uint8_t blueMaskSize{0};
};