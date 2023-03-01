BITS 16
switch_to_pm:
    cli ; Disable interrupts.
    lgdt [gdt_descriptor] ; Set GDT

    ; Set the first bit of the cr0 register, enables
    ; protected mode.
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp CODE_SEG:initialize_pm ; Far jump to following 

BITS 32 ; Indicates the following code is 32 bit instructions.
initialize_pm:

    ; Initializes the segment registers to the same place.
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov gs, ax
    mov fs, ax

    ; Initialize the stack pointers to the top of free space
    mov ebp, 0x90000
    mov esp, ebp


    jmp pm_exit_point