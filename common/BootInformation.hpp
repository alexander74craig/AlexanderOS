#pragma once

#include "stdint.h"
#include "FrameBuffer.hpp"


class BootInformation
{
public:
    //! \brief Parses Multiboot2 information stored at the pointer location in the ebx register.
    //! \details Stores the information so that it is persistent when the memory location may be overridden.
    //! \param ebx[in] Location of the Multiboot2 header.
    explicit BootInformation(void* ebx);

    //! \brief Get accessor for framebuffer information.
    //! \return myFrameBuffer.
    [[nodiscard]] const FrameBuffer& getFrameBuffer() const {return myFrameBuffer;};

private:
    //! \brief Reads 8 bytes and progresses the pointer.
    //! \return The 8 bytes read.
    uint64_t readUint64();
    //! \brief Reads 4 bytes and progresses the pointer.
    //! \return The 4 bytes read.
    uint32_t readUint32();
    //! \brief Reads 2 bytes and progresses the pointer.
    //! \return The 2 bytes read.
    uint16_t readUint16();
    //! \brief Reads a byte and progresses the pointer.
    //! \return The byte read.
    uint8_t readUint8();

    //! \brief Reads the frame buffer tag and progresses the pointer.
    //! \param[in] dataSize Size of the frame buffer tag.
    void readFramebuffer(uint32_t dataSize);

    //! \brief Reads the Memory Map tag and progresses the pointer
    //! \param[in] dataSize Size of the memory map tag.
    void readMemoryMap(uint32_t dataSize);

    //! \brief Current parsing location within the header.
    void* myEbx{};

    //! \brief Frame buffer information.
    FrameBuffer myFrameBuffer{};
};
