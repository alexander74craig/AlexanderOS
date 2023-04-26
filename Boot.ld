ENTRY(_start)
SECTIONS
{
	. = 1M; /* Sets the location in memory to 1 MiB*/
 
	/* Align all sections on 4 KiB boundaries*/
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
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
}