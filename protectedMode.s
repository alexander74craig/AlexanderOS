BITS 16
switchToPm:
    cli ; Disable interrupts
    lgdt [gdtDescriptor] ; Set GDT

    ; Set the first bit of the cr0 register, enables protected mode
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp codeSeg:initializePm ; Far jump to following 

BITS 32 ; Indicates the following code is 32 bit instructions
initializePm:

    ; Initializes the segment registers to the same place in the data segment
    mov ax, dataSeg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax

    ; Initialize the stack pointers to the top of free space
    mov ebp, 0x90000
    mov esp, ebp
    
    ; Jump out to known exit point due to invalidated registers
    jmp pmExitPoint