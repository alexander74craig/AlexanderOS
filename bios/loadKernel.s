
.code16

# Loads the kernel into memory
loadKernel:
    mov $0X2, %ah # Read Sectors From Drive 
    mov $31, %al # read 31 sectors
    mov $0x0, %ch # Cylinder 0
    mov $0x2, %cl # Sector 2 (2nd sector after boot sector)
    mov $0x0, %dh # Head 0
    mov (bootDrive), %dl # Read from boot drive
    mov $kernelOffset, %bx # Set the buffer to the kernel memory location
    int $0x13 # Interrupt to begin read

    jc carryError # Checks carry flag for error
    mov $31, %bl
    cmp %bl, %al # Check if sectors read is 31
    jne sectorReadError # display error message

    ret

# Prints a message that the carry flag was set during reading.
carryError:
    mov $carryErrorMessage, %bx
    call printStringReal
    jmp .

carryErrorMessage:
    .asciz "Carry flag set when reading from disk. "

# Prints an error message that the program failed to read the expected number of sectors from the disk
sectorReadError:
    mov $sectorErrorMessage, %bx
    call printStringReal
    jmp .

sectorErrorMessage:
    .asciz "Failed to read the kernel sectors from the disk. "
