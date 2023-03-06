ENTRY(_start)
OUTPUT_FORMAT(elf64-x86-64)
SECTIONS
{
    . = 0x7c00;

    .text.bootSector :
    {
            *(.text.bootSector)
    }

    .sig : AT(0x7DFE) 
    {
        SHORT(0xaa55);
    }
}