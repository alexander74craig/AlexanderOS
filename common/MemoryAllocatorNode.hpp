#pragma once
#include "stddef.h"

#pragma pack(push, 1)
struct MemoryAllocatorNode {
    //ADDRESS IS WHERE IT IS;
    //! \brief Size in bytes.
    uint64_t size;
    //! \brief Address of next node.
    MemoryAllocatorNode* nextAddress;
};
#pragma pack(pop)
