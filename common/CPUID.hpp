#pragma once
#include "stdint.h"

class CPUID
{
public:
    CPUID();

    bool canHave1GiBPages();

private:
    struct CPUIDRegisters
    {
        //! \brief ECX register value when querying for CPUID information.
        uint32_t EAX{0};
        //! \brief ECX register value when querying for CPUID information.
        uint32_t EBX{0};
        //! \brief ECX register value when querying for CPUID information.
        uint32_t ECX{0};
        //! \brief EDX register value when querying for CPUID information.
        uint32_t EDX{0};
    };

    CPUIDRegisters myCPUID1;
    CPUIDRegisters myCPUID80000001;

};