#pragma once
#include "stddef.h"
#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "MemoryAllocatorNode.hpp"
#include "Memory.hpp"

class MemoryAllocator {
public:
    explicit MemoryAllocator(const MemoryList& memoryList);
    void* alloc(size_t size);
    void free(void* ptr, size_t size);


    MemoryAllocatorNode* myRootAddress;
private:
    void linkMemory(uint64_t address, uint64_t size);
    TextBuffer* myTextBuffer;
};
