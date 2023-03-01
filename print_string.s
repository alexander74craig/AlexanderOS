BITS 32

VIDEO_MEMORY equ 0xb8000 ; Position of video memory for output.
WHITE_ON_BLACK equ 0x0f ; Value of white text on a black background.

print_string:
    pusha
    mov edx, VIDEO_MEMORY

print_character:
    mov al, [ebx] ; Set current character to current position of EBX
    mov ah, WHITE_ON_BLACK ; Set character colors as white on black.

    cmp al, 0
    je exit_print

    mov [edx], ax

    add ebx, 1
    add edx, 2

    jmp print_character

exit_print:
    popa
    ret