#pragma once
#include <stdint.h>

struct MemoryAllocatorNode {
    //ADDRESS IS WHERE IT IS;
    uint64_t size;
    void* nextAddress;
};
