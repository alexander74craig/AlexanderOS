[bits 16]
; Sets the offset for memory to where this file is loaded into memory by BIOS.
[org 0x7c00]

; Switches to protected mode
call switch_to_pm

%include "gdt.s"
%include "print_string.s"
%include "protected_mode.s"


[bits 32]
pm_exit_point: ; Exit point for switch_to_pm after registers are invalidated.

mov ebx, SUCCESS_MESSAGE
call print_string

jmp $ ; Hold position after all else is done.

; Message printed if 32 bit mode is successfully entered.
SUCCESS_MESSAGE db "In 32 bit protected mode", 0

; Padding such that the file is 512 bytes long.
times 510 - ($-$$) db 0

; The magic number that exists at the end of the file denoting that this is the boot sector.
dw 0xaa55
