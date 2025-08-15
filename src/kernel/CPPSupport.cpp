#include <cstddef>

void* operator new(size_t size)
{
    asm("int $0");
}
 
void* operator new[](size_t size)
{
    asm("int $0");
}

void operator delete(void *p, size_t size)
{
    asm("int $0");
}
 
void operator delete[](void *p, size_t size)
{
    asm("int $0");
}

