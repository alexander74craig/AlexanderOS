#include "SerialTextBuffer.hpp"

SerialTextBuffer::SerialTextBuffer(SerialPort port) :
        myPort{port}
{
    outb(static_cast<uint16_t>(myPort) + 1, 0x00);    // Disable all interrupts
    outb(static_cast<uint16_t>(myPort) + 3, 0x80);    //
    outb(static_cast<uint16_t>(myPort) + 0, 0x01);    // Set divisor (low) 1, i.e. 115200 baud rate
    outb(static_cast<uint16_t>(myPort) + 1, 0x00);    // Set divisor (high)
    outb(static_cast<uint16_t>(myPort) + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(static_cast<uint16_t>(myPort) + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(static_cast<uint16_t>(myPort) + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(static_cast<uint16_t>(myPort) + 4, 0x0F);    // Normal mode

    // TODO: Test initialization and create fail-safe state.
}

bool SerialTextBuffer::isTransmitEmpty()
{
    return (inb(static_cast<uint16_t>(myPort)  + 5) & 0x20) != 0;
}

void SerialTextBuffer::writeChar(char character)
{
    while (isTransmitEmpty() == 0){};

    outb(static_cast<uint16_t>(myPort), character);
}

inline void SerialTextBuffer::outb(const uint16_t port, const uint8_t value)
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

inline uint8_t SerialTextBuffer::inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}