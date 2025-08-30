# Multiboot2 Header
.set multibootHeaderSize, multibootHeaderEnd - multibootHeader # Size of the multitboot header

.section .multiboot
.align 8
multibootHeader:
    .long 0xE85250D6 # Magic number that specifies multiboot2
    .long 0x0 # Specifies that the architecture is 32 bit protected mode i386
    .long multibootHeaderSize # Length of the mutliboot header
    .long -(0xE85250D6 + 0x0 + multibootHeaderSize) # Checksum
.align 8
 framebufferTag:
    .word 5 # Type = 5 i.e. framebuffer tag
    .word 0x0 # Flags
    .long 20 # size of tag
    .long 640 # 640 px width
    .long 480 # 480 px height
    .long 32 # 32 bits per pixel
.align 8
endTag:
    .word 0 # Type = End
    .word 0 # Flags = none
    .long 8 # Size, 8 according to the specification of the end tag
multibootHeaderEnd:


.section .bss
.align 16 # Aligns the block on 16 byte memory boundary
stack_bottom: # Sets label for the bottom of the stack
.skip 32768 # Writes 32 kib of 0s
stack_top: # Sets a label for the top of the stack


# Values we need after long jump
.align 8
multibootMagic: .long 0
multibootInfo:  .long 0

.align 4096
pml4:   .skip 4096
.align 4096
pdpt:   .skip 4096
.align 4096
pd:     .skip 4096



.section .text
.global _start
.type _start, @function
.code32
_start:

    cli # Disable interrupts

    # Set GDT.
    # Describes a flat memory model with 2 segment descriptors, Kernel Code and Kernel Data/
    # Both segments span from 0 to 4 GiB.
    lgdt (gdtDescriptor)

    # Long jump to set cs register
   ljmp *postGDTLongJump_ptr
postGDTLongJump_ptr:
   .long postGDTLongJump
   .word codeSeg32

    postGDTLongJump:

    # Set Segment registers.
    mov $dataSeg, %dx
    mov %dx, %ds
    mov %dx, %ss
    mov %dx, %es
    mov %dx, %gs
    mov %dx, %fs
    mov $stack_top, %esp # Sets the top of the stack


    mov %ebx, multibootInfo # Saves EBX as it contains the info header location from the GRUB bootloader
    mov %eax, multibootMagic # Saves EAX as it contains the magic number from the GRUB bootloader.

    # PML4[0] -> PDPT, present, read, and write enabled.
    mov $pml4, %edi
    mov $pdpt, %eax
    or $0x3, %eax # Sets flags to be present and read/write enabled
    mov %eax, (%edi)
    mov $0, 4(%edi)

    # Identity map 512 GiB using 1 GiB pages via PDPT entries
    # PDPT[i] = (i * 1GiB) | P | RW | PS
    mov $pdpt, %edi
    xor %edx, %edx            # Zero out high bits of working address
    xor %eax, %eax            # Zero out low bits of working address
    mov $512, %ecx            # Number of times to loop through
.LoopFillPDPT:
    mov %eax, %ebx
    or  $0x83, %ebx           # Set flags for present, read/write, and PS (1GiB page)
    mov %ebx, 0(%edi)         # Write low 32 bits (address low + flags)
    mov %edx, 4(%edi)         # Write high 32 bits (address high)
    add $0x40000000, %eax     # Advance address low by 1 GiB
    adc $0, %edx              # Propagate carry into address high
    add $8, %edi              # Next PDPT entry
    loop .LoopFillPDPT

    # Point cr3 register at pml4 table
    mov $pml4, %eax
    mov %eax, %cr3

    # Enable PAE
    mov %cr4, %eax
    bts $5, %eax
    mov %eax, %cr4

    # Enable long mode
    mov $0xC0000080, %ecx # IA32_EFER
    rdmsr
    bts $8, %eax
    wrmsr

    # Enable paging
    mov %cr0, %eax
    bts $31, %eax
    mov %eax, %cr0

   ljmp *longModeStart_ptr
longModeStart_ptr:
   .long longModeStart
   .word codeSeg


.code64
longModeStart:

    # Load segment registers
    mov $dataSeg, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs

    # Enable SSE for x86_64 C++ code
    mov %cr0, %rax
    and $~(1 << 2), %rax     # clear EM (bit 2) – disable FPU emulation
    or  $(1 << 1), %rax      # set MP (bit 1) – monitor coprocessor
    and $~(1 << 3), %rax     # clear TS (bit 3): task switched
    mov %rax, %cr0
    clts
    mov %cr4, %rax
    or  $((1 << 9) | (1 << 10)), %rax   # OSFXSR (bit 9), OSXMMEXCPT (bit 10)
    mov %rax, %cr4
    fninit # Initialize FPU

    lea stack_top(%rip), %rsp
    sub $8, %rsp

    # Initialize the IDT so that interrupts can be handled
    call initializeInterruptDescriptorTable

    # Disabled the PIC
    mov $0xff, %al
    out %al, $0x21
    out %al, $0xa1

    # Pass cpuid and multiboot information to main.
    mov multibootMagic(%rip), %eax
    mov %eax, %edi
    mov multibootInfo(%rip), %eax
    mov %eax, %esi

    .align 16 # Aligns to 16 bytes before call to kernel.
    call main # Calls kernel main.

# Loop here if returned from kernel
halt:
    cli # Disable interrupts
    hlt
    jmp halt
