#include "CPUID.hpp"

CPUID::CPUID()
{
    asm volatile(
        "cpuid"
        : "=a"(myCPUID1.EAX), "=b"(myCPUID1.EBX), "=c"(myCPUID1.ECX), "=d"(myCPUID1.EDX)
        : "a"(1)
        : "memory"
        );
    asm volatile(
        "cpuid"
        : "=a"(myCPUID80000001.EAX), "=b"(myCPUID80000001.EBX), "=c"(myCPUID80000001.ECX), "=d"(myCPUID80000001.EDX)
        : "a"(0x80000001u), "c"(0u)
        : "memory"
    );
}

bool CPUID::canHave1GiBPages()
{
    return myCPUID80000001.EDX & (1 << 26);
}