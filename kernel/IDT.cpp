#include "stdint.h"

extern "C"
{
#pragma pack(push, 1)
//! \brief IDT entry
struct GateDescriptor
{
    uint16_t    ISR_AddressLow; // The lower 16 bits of the ISR's address
	uint16_t    segmentSelector; // The GDT segment that the CPU will load into CS before calling the ISR
	uint8_t     reserved; // Reserved 0'd out space
    uint8_t     flags; // Flags used to specify type of gate of the interrupt entry
	uint16_t    ISR_AddressHigh; // The higher 16 bits of the ISR's address
};
#pragma pack(pop)

#pragma pack(push, 1)
//! \brief Struct representing the value of the interrupt descriptor table register.
struct IDTR
{	
    uint16_t limit; // Limit of address
	uint32_t base; // Base of address
};
#pragma pack(pop)

//! \brief Function called when interrupts occur
//! \param[in] interruptIndex Index of the calling interrupt within the interrupt table.
void handleInterrupt(uint32_t interruptIndex)
{
    asm("hlt");
}

#pragma pack(push, 16)
// Interrupt descriptor table.
static GateDescriptor idt[256];
#pragma pack(pop)

static IDTR idtr;

// Access the value of the code segment offset from the GDT
extern uint32_t codeSeg;
#define codeSegValue ((uint32_t) (&codeSeg))

void setGateDescriptor(uint8_t index, void* isr, uint8_t flags)
{
    GateDescriptor* descriptor = &idt[index];

    descriptor->ISR_AddressLow = reinterpret_cast<uint32_t>(isr) & 0xFFFF;
    descriptor->segmentSelector = codeSegValue;
    descriptor->reserved = 0x00;
    descriptor->flags = flags;
    descriptor->ISR_AddressHigh = reinterpret_cast<uint32_t>(isr) >> 16;
}

extern void* interruptServiceRoutineTable[];

//! \brief Initializes the interrupt descriptor table with the addresses of the interrupt service routines
void initializeInterruptDescriptorTable()
{
    constexpr uint32_t numberOfGateDescriptors{32};
    idtr.base = reinterpret_cast<uint32_t>(&idt[0]);
    idtr.limit =static_cast<uint16_t>(sizeof(GateDescriptor)) * numberOfGateDescriptors - 1;

    for (uint32_t index {0}; index < numberOfGateDescriptors; index++)
    {
        setGateDescriptor(index, interruptServiceRoutineTable[index], 0x8E);
    }

    // Load the IDT
    asm("lidt %0" : : "m"(idtr));
    // Enable interrupts
    asm("sti");
}
}
