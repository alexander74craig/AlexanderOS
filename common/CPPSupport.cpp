#include "stddef.h"
#include "MemoryAllocator.hpp"


void* operator new(size_t size)
{
    return MemoryAllocator::instance().alloc(size);
}

void* operator new[](size_t size)
{
    return MemoryAllocator::instance().alloc(size);
}

void operator delete(void *p, size_t size)
{
    MemoryAllocator::instance().free(p, size);
}

void operator delete[](void *p, size_t size)
{
    MemoryAllocator::instance().free(p, size);
}

