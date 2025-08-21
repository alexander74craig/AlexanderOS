#pragma once
#include "stddef.h"

struct alignas(16) MemoryAllocatorNode {
    //ADDRESS IS WHERE IT IS;
    //! \brief Size in bytes.
    size_t size;
    //! \brief Address of the next node.
    MemoryAllocatorNode* nextAddress;
};

static_assert((alignof(MemoryAllocatorNode) % 16) == 0, "MemoryAllocatorNode not aligned");
