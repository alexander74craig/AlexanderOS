#pragma once
#include "stddef.h"
#include "BootInformation.hpp"
#include "DirectDisplayTextBuffer.hpp"
#include "MemoryAllocatorNode.hpp"

class MemoryAllocator {
public:
    //! \brief Singleton constructor. Makes an empty allocator.
    //! \return Singleton instance of the memory allocator.
    static MemoryAllocator& instance() {
        static MemoryAllocator instance;
        return instance;
    }

    //! \brief Deleted copy constructor.
    MemoryAllocator(const MemoryAllocator&) = delete;
    //! \brief Deleted copy assignment operator.
    MemoryAllocator& operator=(const MemoryAllocator&) = delete;
    //! \brief Deleted move constructor.
    MemoryAllocator(MemoryAllocator&&) = delete;
    //! \brief Deleted move assignment operator.
    MemoryAllocator& operator=(MemoryAllocator&&) = delete;

    //! \brief Allocates memory of the given size requested.
    //! \param[in] size Number of bytes of memory block to allocate, is rounded up to next multiple of 16.
    //! \return Pointer to allocated memory block.
    void* alloc(size_t size);

    //! \brief Frees memory at the given location of the given size.
    //! \param[in, out] ptr Address to free.
    //! \param[in] size Size of memory to free, rounded up to the next multiple of 16.
    void free(void* ptr, size_t size);

    //! \brief Allocates all the memory blocks in the given list as free memory to allocate.
    //! \param[in] memory List of memory blocks to be used for allocation.
    void initializeMemory(const MemoryList& memory);

    //! \brief Calculates the total amount of free memory left.
    //! \return The total free memory currently available for allocation.
    [[nodiscard]] uint64_t getFreeMemorySize() const;

    //! \brief Calculates the total number of free memory blocks
    //! \return Total number of free memory blocks.
    [[nodiscard]] uint64_t getFragmentation() const;

    //! \brief Gets the total memory size, including allocated memory.
    //! \return myTotalSize.
    [[nodiscard]] uint64_t getTotalMemorySize() const;

private:
    //! \brief Head of the linked list of free memory blocks.
    MemoryAllocatorNode* myRootAddress{nullptr};

    //! \brief Hidden default constructor.
    MemoryAllocator() = default;

    //! \brief Total size of memory, including allocated.
    uint64_t myTotalSize{0};

    //! \brief Calculates the next value aligned to 16.
    //! \param[in] toAlign Value to align to 16.
    //! \return The next value aligned to 16.
    static uint64_t align(uint64_t toAlign);

    //! \brief Links a block of memory to the list of free memory.
    //! \param[in] address Address to link.
    //! \param[in] size Size of block to link
    void linkMemory(uint64_t address, uint64_t size);

    //! \brief Aligns the address and size of a given block.
    //! \param[in,out] address Address to be aligned.
    //! \param[in,out] size Size to be aligned.
    static void alignBlock(uint64_t& address, uint64_t& size);
};
