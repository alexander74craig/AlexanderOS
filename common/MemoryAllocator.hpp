#pragma once
#include "stddef.h"
#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "MemoryAllocatorNode.hpp"
#include "Memory.hpp"

class MemoryAllocator {
public:

    static MemoryAllocator& instance() {
        static MemoryAllocator instance;
        return instance;
    }

    MemoryAllocator(const MemoryAllocator&) = delete;
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;
    MemoryAllocator(MemoryAllocator&&) = delete;
    MemoryAllocator& operator=(MemoryAllocator&&) = delete;

    void* alloc(size_t size);
    void free(void* ptr, size_t size);
    void linkMemory(uint64_t address, uint64_t size);

    MemoryAllocatorNode* myRootAddress;
private:
    MemoryAllocator() : myRootAddress{nullptr} {};

};
