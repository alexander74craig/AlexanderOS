ENTRY(_start)
OUTPUT_FORMAT(elf64-x86-64)
OUTPUT_ARCH(i386:x86-64)

SECTIONS
{
	. = 2M; /* Sets the location in memory to 2 MiB*/
    kernelStart = .;
	/* Align all sections on 4 KiB boundaries*/
	.text BLOCK(4K) : ALIGN(4K)
	{
		KEEP(*(.multiboot))
		*(.text)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(.bss)
	}
	.stack BLOCK(4k) : ALIGN (4k)
	{
		*(.stack)
	}
	kernelEnd = .;
}