#pragma once

#include "StandardDefinitions.hpp"

struct MemoryMapEntry {
    uint64_t baseAddress;
    uint64_t length;
    uint32_t type;
};