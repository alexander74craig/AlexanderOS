BITS 32

videoMemory equ 0xb8000 ; Position of video memory for output.
whiteOnBlack equ 0x0f ; Value of white text on a black background.

printString:
    pusha
    mov edx, videoMemory

printCharacter:
    mov al, [ebx] ; Set current character to current position of EBX
    mov ah, whiteOnBlack ; Set character colors as white on black.

    cmp al, 0 ; Checks if at end of string (null character)
    je exitPrint

    mov [edx], ax ; Moves character and color format to video memory position.

    add ebx, 1 ; Increments one character in message memory.
    add edx, 2 ; Increments one character in video memory.

    jmp printCharacter

exitPrint:
    popa
    ret