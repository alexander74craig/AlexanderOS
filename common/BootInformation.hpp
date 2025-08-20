#pragma once

#include "stdint.h"


class BootInformation
{
public:
    explicit BootInformation(void* ebx);

    // Framebuffer type = 8
    // Address of frame buffer.
    uint64_t framebufferAddress{};
    // Bytes per line. IE width * BPP
    uint32_t framebufferPitch{};
    // Width in pixels, or characters if framebufferType = 2
    uint32_t framebufferWidth{};
    // Height in pixels, or characters if framebufferType = 2
    uint32_t framebufferHeight{};
    // Bits per pixel
    uint8_t framebufferBitsPerPixel{};
    // Frame buffer type 0 = Indexed color, 1 = direct RGB, 2 = EGA Text
    uint8_t framebufferType{};
    uint8_t framebufferRedFieldPosition{};
    uint8_t framebufferRedMaskSize{};
    uint8_t framebufferGreenFieldPosition{};
    uint8_t framebufferGreenMaskSize{};
    uint8_t framebufferBlueFieldPosition{};
    uint8_t framebufferBlueMaskSize{};

private:
    uint64_t readUint64();
    uint32_t readUint32();
    uint16_t readUint16();
    uint8_t readUint8();

    void readFramebuffer(uint32_t dataSize);
    void readMemoryMap(uint32_t dataSize);

    void* myEbx{};
};
