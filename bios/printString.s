.code32

.set videoMemory, 0xb8000 # Position of video memory for output
.set whiteOnBlack, 0x0f # Value of white text on a black background

printString:
    pusha
    mov $videoMemory, %edx

printCharacter:
    mov  (%ebx), %al # Set current character to current position of EBX
    mov  $whiteOnBlack, %ah # Set character colors as white on black

    cmp $0, %al # Checks if at end of string (null character)
    je exitPrint

    mov %ax, (%edx) # Moves character and color format to video memory position

    add $1, %ebx # Increments one character in message memory
    add $2, %edx # Increments one character in video memory

    jmp printCharacter

exitPrint:
    popa
    ret

# Prints a message used for debugging.
printDebug:
    pusha
    mov $debugMessage, %ebx
    popa
    ret
debugMessage:
    .asciz "Protected mode debug message."
