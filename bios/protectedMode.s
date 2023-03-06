.code16

switchToPm:
    cli # Disable interrupts
    lgdt (gdtDescriptor) # Set GDT

    # Set the first bit of the cr0 register, enables protected mode
    mov %cr0, %eax
    or $1, %eax
    mov %eax, %cr0

    jmp $codeSeg, $initializePm # Far jump to following 

.code32 # Indicates the following code is 32 bit instructions
initializePm:

    # Initializes the segment registers to the same place in the data segment
    mov $dataSeg, %ax
    mov %ax, %ds
    mov %ax, %ss
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs

    # Initialize the stack pointers to the top of free space
    mov $0x90000, %ebp 
    mov %ebp, %esp
    
    # Jump out to known exit point due to invalidated registers
    jmp pmExitPoint
