.code16

printStringReal:
    pusha
    mov $0x0e,  %ah 

printCharacterReal:
    mov (%bx), %al # Set current character to current position of EBX

    cmp $0, %al # Checks if at end of string (null character)
    je exitPrintReal

    int $0x10 # Prints al
    add $1, %bx # Increments one character in message memory

    jmp printCharacterReal

exitPrintReal:
    popa
    ret

# Prints a message to be used for debugging.
printDebugReal:
    pusha
    mov $debugHere, %bx
    call printStringReal
    popa
    ret
debugHere:
    .asciz "Real mode debug message"
