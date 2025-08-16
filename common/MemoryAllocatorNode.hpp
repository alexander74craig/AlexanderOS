#pragma once
#include "stddef.h"

#pragma pack(push, 1)
struct MemoryAllocatorNode {
    //ADDRESS IS WHERE IT IS;
    uint64_t length;
    MemoryAllocatorNode* nextAddress;
};
#pragma pack(pop)
