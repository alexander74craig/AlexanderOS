# Multiboot Header
.set ALIGN, 1<<0 # multiboot flag, align modules on page boundaries
.set MEMINFO, 1<<1 # multiboot flag, yes memory map
.set FLAGS, ALIGN | MEMINFO # Flag field
.set MAGIC, 0x1BADB002 # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # Checksum for the multiboot information

.section .multiboot
.align 4 # Aligns the multiboot flags on the 32-bit boundary.
.long MAGIC
.long FLAGS
.long CHECKSUM


.section .bss
.align 16 # Aligns the block on 16 byte memory boundary
stack_bottom: # Sets label for the bottom of the stack
.skip 16384 # Writes 16kb of 0s
stack_top: # Sets a label for the top of the stack


.section .text
.global _start
.type _start, @function
_start:

# TODO: Set up GDT
# TODO: Set up IDT


	mov $stack_top, %esp # Sets the top of the stack
    call main # Calls kernel main.
    cli # Disable interupts
# Loop here if returned from kernel
halt:
    hlt
    jmp halt
