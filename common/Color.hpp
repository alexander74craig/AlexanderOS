#pragma once

#include "stdint.h"

//! \brief Describes a color
class Color
{
public:
    //! \brief Constructor
    //! \param[in] red Red level.
    //! \param[in] green Green level.
    //! \param[in] red Blue level.
    constexpr Color(uint8_t red, uint8_t green, uint8_t blue) : red{red}, green{green}, blue{blue}{}

    //! \brief Default constructor to black.
    constexpr Color() : red{0}, green{0}, blue{0} {};

    //! \brief Red level.
    uint8_t red;
    //! \brief Green level.
    uint8_t green;
    //! \brief Blue level.
    uint8_t blue;
};