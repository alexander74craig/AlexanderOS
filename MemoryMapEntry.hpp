#pragma once

#include <stdint.h>

struct MemoryMapEntry
{
    uint64_t baseAddress{0};
    uint64_t length{0};
    uint32_t type{0};
};
