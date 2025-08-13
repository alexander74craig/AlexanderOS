#pragma once
#include <stdint.h>

#include "BootInformation.hpp"
#include <stddef.h>
#include "DirectDisplayTextBuffer.hpp"
#include "MemoryAllocatorNode.h"

class MemoryAllocator {
public:
    explicit MemoryAllocator(const BootInformation& bootInformation, DirectDisplayTextBuffer& textBuffer);
    void* alloc(size_t size);
    void free(void* ptr, size_t size);

    MemoryAllocatorNode* myRootAddress;
private:

};
