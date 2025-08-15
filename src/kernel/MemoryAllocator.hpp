#pragma once
#include "StandardDefinitions.hpp"
#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "MemoryAllocatorNode.hpp"

class MemoryAllocator {
public:
    explicit MemoryAllocator(const BootInformation& bootInformation, DirectDisplayTextBuffer& textBuffer);
    void* alloc(size_t size);
    void free(void* ptr, size_t size);

    MemoryAllocatorNode* myRootAddress;
private:

};
