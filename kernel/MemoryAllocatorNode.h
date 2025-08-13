#pragma once
#include <stdint.h>

#pragma pack(push, 1)
struct MemoryAllocatorNode {
    //ADDRESS IS WHERE IT IS;
    uint64_t size;
    MemoryAllocatorNode* nextAddress;
};
#pragma pack(pop)
