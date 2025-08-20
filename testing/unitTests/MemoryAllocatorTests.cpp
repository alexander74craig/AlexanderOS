#include "MemoryAllocator.hpp"
#include "gtest/gtest.h"

TEST(MemoryAllocator, allocation)
{
    uint8_t byeArrayA[180000];
    uint8_t byeArrayB[120000];
    uint8_t byeArrayC[160000];

    MemoryAllocator::instance().linkMemory(reinterpret_cast<uint64_t>(byeArrayA), 180000);
    MemoryAllocator::instance().linkMemory(reinterpret_cast<uint64_t>(byeArrayB), 120000);
    MemoryAllocator::instance().linkMemory(reinterpret_cast<uint64_t>(byeArrayC), 160000);
}