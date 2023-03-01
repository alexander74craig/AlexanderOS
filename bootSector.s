BITS 16
; Sets the offset for memory to where this file is loaded into memory by BIOS.
[org 0x7c00]

; Switches to protected mode
call switchToPm

%include "gdt.s"
%include "printString.s"
%include "protectedMode.s"

BITS 32
pmExitPoint: ; Exit point for switch_to_pm after registers are invalidated.

mov ebx, successMessage
call printString

jmp $ ; Hold position after all else is done.

; Message printed if 32 bit mode is successfully entered.
successMessage db "In 32 bit protected mode", 0

; Padding such that the file is 512 bytes long.
times 510 - ($-$$) db 0

; The magic number that exists at the end of the file denoting that this is the boot sector.
dw 0xaa55
