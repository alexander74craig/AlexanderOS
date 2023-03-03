BITS 16
printStringReal:
    pusha
    mov ah, 0x0e

printCharacterReal:
    mov al, [bx] ; Set current character to current position of EBX

    cmp al, 0 ; Checks if at end of string (null character)
    je exitPrint

    int 0x10 ; Prints al
    add bx, 1 ; Increments one character in message memory

    jmp printCharacterReal

exitPrintReal:
    popa
    ret

; Prints a message to be used for debugging.
printDebugReal:
    pusha
    mov bx, debugHere
    call printStringReal
    popa
    ret
debugHere db "Real mode debug message", 0