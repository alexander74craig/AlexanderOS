BITS 16
; Loads the kernel into memory
loadKernel:
    mov ah, 0X2 ; Read Sectors From Drive 
    mov al, 31 ; read 31 sectors
    mov ch, 0x0 ; Cylinder 0
    mov cl, 0x2 ; Sector 2 (2nd sector after boot sector)
    mov dh, 0x0 ; Head 0
    mov dl, [bootDrive] ; Read from boot drive
    mov bx, kernelOffset ; Set the buffer to the kernel memory location
    int 0x13 ; Interrupt to begin read
    
    jc carryError ; Checks carry flag for error
    mov bl, 31
    cmp bl, al ; Check if sectors read is 31
    jne sectorReadError ; display error message

    ret

; Prints a message that the carry flag was set during reading.
carryError:
    mov bx, carryErrorMessage
    call printStringReal
    jmp $
    carryErrorMessage db "Carry flag set when reading from disk.", 0

; Prints an error message that the program failed to read the expected number of sectors from the disk
sectorReadError:
    mov bx, sectorErrorMessage
    call printStringReal
    jmp $
    sectorErrorMessage db "Failed to read the kernel sectors from the disk.", 0