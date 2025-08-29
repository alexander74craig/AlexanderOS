#pragma once
#include <stdint.h>
#include "TextBuffer.hpp"

//! \brief Possible serial ports.
enum class SerialPort
{
    COM1 = 0x3f8,
    COM2 = 0x2f8,
    COM3 = 0x3e8,
    COM4 = 0x2e8,
};

//! \brief Text buffer for a serial port
class SerialTextBuffer : public TextBuffer
{
public:
    //! \brief Initializes a serial port.
    //! \param[in] port Port to initialize.
    SerialTextBuffer(SerialPort port);

    //! \brief Virtual destructor used for polymorphism.
    virtual ~SerialTextBuffer() = default;

private:
    //! \brief Port to write to.
    SerialPort myPort;

    //! \brief Checks if the transmit buffer is empty to delay writing another character.
    bool isTransmitEmpty();

    //! \brief Writes a character to the serial port.
    //! \param[in] character Character to write.
    void writeChar(char character) override;

    //! \brief Puts a value at the given port address.
    //! \param[in] port Port to write to.
    //! \param[in] value Value to write.
    static inline void outb(uint16_t port, uint8_t value);

    //! \brief Reads a value from the given port.
    //! \param[in] port Port to read from.
    static inline uint8_t inb(uint16_t port);
};