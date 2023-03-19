# Multiboot2 Header
.set multibootHeaderSize, multibootHeaderEnd - multibootHeader # Size of the multitboo header

.section .multiboot
.align 8
multibootHeader:
    .long 0xE85250D6 # Magic number that specifies multiboot2
    .long 0x0 # Specifies that the architecture is 32 bit protected mode i386
    .long multibootHeaderSize # Length of the mutliboot header
    .long -(0xE85250D6 + 0x0 + multibootHeaderSize) # Checksum
.align 8
endTag:
    .word 0 # Type = End
    .word 0 # Flags = none
    .long 8 # Size, 8 according to the specification of the end tag
multibootHeaderEnd:


.section .bss
.align 16 # Aligns the block on 16 byte memory boundary
stack_bottom: # Sets label for the bottom of the stack
.skip 16384 # Writes 16kb of 0s
stack_top: # Sets a label for the top of the stack


.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp # Sets the top of the stack

    # Set GDT.
    # Describes a flat memory model with 2 segment descriptors, Kernel Code and Kernel Data/
    # Both segments span from 0 to 4 GiB.
    # lgdt (gdtDescriptor) 


    # Initialize the IDT so that interrupts 
    # call initializeInterruptDescriptorTable

    .align 16 # Aligns to 16 bytes before call to kernel.
    push %ebx # Pushes EBX as an argument to main
    push %eax # Pusehs EAX as an argument to main
    call main # Calls kernel main.

# Loop here if returned from kernel
    cli # Disable interupts
halt:
    hlt
    jmp halt

.include "gdt.s"
