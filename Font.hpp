#pragma once

#include <stdint.h>

class Font
{
private:

    uint8_t myGlyphs[4096];

public:
    Font();

    uint8_t* getGlyph(char character);
};