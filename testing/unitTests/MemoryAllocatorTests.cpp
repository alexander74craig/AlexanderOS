#include "MemoryAllocator.hpp"
#include "gtest/gtest.h"

//! \test Tests that contiguous memory blocks linked out of order will coalesce correctly into a continuous block.
TEST(MemoryAllocator, coalescence)
{
    constexpr  uint64_t size{1600};

    struct alignas(16) PackedMemory
    {
        uint8_t byeArrayA[size];
        uint8_t byeArrayB[size];
        uint8_t byeArrayC[size];
        uint8_t byeArrayD[size];
        uint8_t byeArrayE[size];
        uint8_t byeArrayF[size];
        uint8_t byeArrayG[size];
    };

    PackedMemory memory{};
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayA), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayF), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayG), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayC), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayB), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayE), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayD), size});

    MemoryAllocator::instance().initializeMemory(memoryList);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 7);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), size * 7);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 1);
}

//! \test Tests that the allocator will align block sizes.
TEST(MemoryAllocator, blockSizeAlignment)
{
    alignas(16) uint8_t buffer[1600];
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(buffer), 1600 - 1});
    MemoryAllocator::instance().initializeMemory(memoryList);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), 1600 - 16);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), 1600 - 16);
}

//! \test Tests that the allocator will align block addresses.
TEST(MemoryAllocator, blockAddressAlignment)
{
    alignas(16) uint8_t buffer[1600];
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(buffer) + 1, 1200});
    MemoryAllocator::instance().initializeMemory(memoryList);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), 1200 - 16);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), 1200 - 16);
}

//! \test Tests that the allocator will align block addresses and sizes simultaneously.
TEST(MemoryAllocator, blockAlignment)
{
    alignas(16) uint8_t buffer[1600];
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(buffer) - 1, 1600 + 1});
    MemoryAllocator::instance().initializeMemory(memoryList);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), 1600);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), 1600);
}

//! \test Tests that the allocator will align allocations.
TEST(MemoryAllocator, allocAlignment)
{
    alignas(16) uint8_t buffer[1600];
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(buffer), 1600});
    MemoryAllocator::instance().initializeMemory(memoryList);
    EXPECT_EQ(MemoryAllocator::instance().getTotalMemorySize(), 1600);

    void* p1{MemoryAllocator::instance().alloc(1)};
    void* p2{MemoryAllocator::instance().alloc(17)};
    void* p3{MemoryAllocator::instance().alloc(31)};
    void* p4{MemoryAllocator::instance().alloc(128)};
    void* p5{MemoryAllocator::instance().alloc(3)};
    void* p6{MemoryAllocator::instance().alloc(1055)};


    auto isAligned = [](void* p)
    {
        return ((reinterpret_cast<uint64_t>(p) & 15) == 0);
    };

    ASSERT_TRUE(isAligned(p1));
    ASSERT_TRUE(isAligned(p2));
    ASSERT_TRUE(isAligned(p3));
    ASSERT_TRUE(isAligned(p4));
    ASSERT_TRUE(isAligned(p5));
    ASSERT_TRUE(isAligned(p6));

    EXPECT_EQ(MemoryAllocator::instance().getFreeMemorySize(), 1600 - (16 + 32 + 32 + 128 + 16 + 1056));

    MemoryAllocator::instance().free(p1, 1);
    MemoryAllocator::instance().free(p2, 17);
    MemoryAllocator::instance().free(p3, 31);
    MemoryAllocator::instance().free(p4, 128);
    MemoryAllocator::instance().free(p5, 3);
    MemoryAllocator::instance().free(p6, 1055);

    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), 1600);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 1);
}

//TODO: Add test fully emptying a free memory block.
TEST(MemoryAllocator, emptyBlock)
{
    constexpr  uint64_t size{1600};

    struct alignas(16) PackedMemory
    {
        uint8_t byeArrayA[size];
        uint8_t byeArrayB[size];
        uint8_t byeArrayC[size];
        uint8_t byeArrayD[size];
        uint8_t byeArrayE[size];
        uint8_t byeArrayF[size];
        uint8_t byeArrayG[size];
        uint8_t byeArrayH[size];
    };

    PackedMemory memory{};
    MemoryList memoryList{};
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayA), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayC), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayD), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayF), size});
    memoryList.pushBack({reinterpret_cast<uint64_t>(memory.byeArrayH), size});

    MemoryAllocator::instance().initializeMemory(memoryList);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 5);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), size * 5);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 4);

    void* fullBlock{MemoryAllocator::instance().alloc(size)};
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 4);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 3);

    MemoryAllocator::instance().free(fullBlock, size);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 5);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 4);

    void* doubleBlock{MemoryAllocator::instance().alloc(size*2)};
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 3);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 3);

    MemoryAllocator::instance().free(doubleBlock, size*2);
    ASSERT_EQ(MemoryAllocator::instance().getFreeMemorySize(), size * 5);
    ASSERT_EQ(MemoryAllocator::instance().getTotalMemorySize(), size * 5);
    ASSERT_EQ(MemoryAllocator::instance().getFragmentation(), 4);
}

// TODO: Add test case for attempting to allocate at nullptr?