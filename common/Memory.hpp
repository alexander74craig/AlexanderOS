#pragma once
#include "stdint.h"
#include "stddef.h"

//! \brief A contiguous block of memory.
struct MemoryBlock
{
    //! \brief Constructor
    //! \param[in] address Address of the start of the block.
    //! \param[in] size Size of the block in bytes.
    MemoryBlock(uint64_t address, uint64_t size) : address{address}, size{size} {};

    //! \brief Default constructor
    MemoryBlock() : address{0}, size{0} {};

    //! \brief Address of the start of the block.
    uint64_t address;

    //! \brief Size of the block in bytes.
    uint64_t size;
};

//! \brief Class representing a list of memory blocks. Statically sized.
class MemoryList
{
public:
    //! \brief Default constructor that initializes an empty list.
    MemoryList();

    //! \brief Pushes back a block to the next available index.
    //! \details If there is no remaining space it will ignore this request.
    //! \param[in] block Block to push back.
    void pushBack(const MemoryBlock& block);

    //! \brief Gets the number of currently pushed back blocks in the list.
    //! \return mySize.
    size_t size() const;

    //! \brief Get accessor for the block at a given index.
    //! \details If the request falls outsides the bounds of the blocks pushed
    //      onto this list, a defaulted block is returned.
    //! \return Block at requested index, or defaulted block if index is invalid.
    MemoryBlock at(size_t index) const;
private:
    //! \brief Array holding possible blocks.
    MemoryBlock myMemory[128];

    //! \brief Number of blocks currently stored in the list.
    size_t mySize;
};