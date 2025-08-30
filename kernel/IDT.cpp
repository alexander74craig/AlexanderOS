#include <SerialTextBuffer.hpp>

#include "stdint.h"
#include "EGATextBuffer.hpp"
extern "C"
{
#pragma pack(push, 1)
//! \brief IDT entry
struct GateDescriptor
{
    uint16_t ISR_AddressLow;  // ISR address bits 0-15
    uint16_t segmentSelector; // Selects a code segment in the GDT
    uint8_t  IST;             // IST bits 0-2 holds, else reserved zeros
    uint8_t  flags;           // Gate type 0-3, Reserved 4, DPL 5-6, P 7.
    uint16_t ISR_AddressMed;  // ISR address bits 16-31
    uint32_t ISR_AddressHigh; // ISR address bits 32-63
    uint32_t zero;            // Reserved
};
#pragma pack(pop)

#pragma pack(push, 1)
//! \brief Struct representing the value of the interrupt descriptor table register.
struct IDTR
{
    uint16_t limit; // Limit of address
	uint64_t base;  // Base of address
};
#pragma pack(pop)

//! \brief Function called when interrupts occur
//! \param[in] interruptIndex Index of the calling interrupt within the interrupt table.
void handleInterrupt(uint64_t interruptIndex)
{
    SerialTextBuffer serial{SerialPort::COM1};
    serial.write("\nInterrupt: ");
    serial.write(interruptIndex);
    if (interruptIndex == 0xe) // Page fault.
    {
        uint64_t faultAddress;
        asm volatile ("mov %%cr2, %0" : "=r"(faultAddress));
        serial.write("\nPage fault address: ");
        serial.write(faultAddress);
        serial.write("\n");

    }
    asm volatile ("cli; hlt");
}

#pragma pack(push, 16)
// Interrupt descriptor table.
static GateDescriptor idt[256];
#pragma pack(pop)

static IDTR idtr;

extern uint16_t codeSegSelector;
void setGateDescriptor(uint8_t index, void* isr, uint8_t flags)
{
    GateDescriptor* descriptor = &idt[index];

    descriptor->ISR_AddressLow = reinterpret_cast<uint64_t>(isr) & 0xFFFF;
    descriptor->segmentSelector = codeSegSelector; // Code segment selector
    descriptor->IST = 0;
    descriptor->flags = flags;
    descriptor->ISR_AddressMed = (reinterpret_cast<uint64_t>(isr) >> 16) & 0xFFFF;
    descriptor->ISR_AddressHigh = (reinterpret_cast<uint64_t>(isr) >> 32) & 0xFFFFFFFF;
    descriptor->zero = 0;
}

extern void* interruptServiceRoutineTable[];

//! \brief Initializes the interrupt descriptor table with the addresses of the interrupt service routines
void initializeInterruptDescriptorTable()
{
    constexpr uint32_t numberOfGateDescriptors{256};
    idtr.base = reinterpret_cast<uint64_t>(&idt[0]);
    idtr.limit =static_cast<uint16_t>(sizeof(GateDescriptor)) * numberOfGateDescriptors - 1;

    for (uint32_t index {0}; index < numberOfGateDescriptors; index++)
    {
        setGateDescriptor(index, interruptServiceRoutineTable[index], 0x8E);
    }

    // Load the IDT
    asm("lidt %0" : : "m"(idtr));
}
}
