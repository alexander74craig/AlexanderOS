#pragma once
#include <stdint.h>

#include "BootInformation.hpp"
#include <stddef.h>

class MemoryAllocator {
public:
    explicit MemoryAllocator(const BootInformation& bootInformation);
    void* alloc(size_t size);
    void free(void* ptr, size_t size);
private:
    void* myRootAddress;
    uint64_t myRootSize;
};
