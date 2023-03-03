BITS 16
; Sets the offset for memory to where this file is loaded into memory by BIOS
[org 0x7c00]
kernelOffset equ 0x1000 ; Memory location to load the kernel at

mov [bootDrive], dl ; Reads boot drive into memory

; Notifies user that the kernel is being loaded
mov bx, loadingKernelMessage 
call printStringReal
call loadKernel

; Notifies the user and switches to protected mode
mov bx, pmSwitchMessage 
call printStringReal
call switchToPm

%include "loadKernel.s"
%include "printStringReal.s"
%include "gdt.s"
%include "printString.s"
%include "protectedMode.s"

BITS 32
pmExitPoint: ; Exit point for switch_to_pm after registers are invalidated

mov ebx, pmSuccessMessage
call printString

call kernelOffset ; Jump to kernelEntryPoint.s as loaded into memory.

jmp $ ; Hold position after all else is done

; Messages for various execution points.
loadingKernelMessage db "Loading kernel. ", 0
pmSwitchMessage db "Switching to protected mode. ", 0
pmSuccessMessage db "Successfully switched to protected mode.", 0
; Location to store drive number of the boot drive
bootDrive db 0


; Padding such that the file is 512 bytes long
times 510 - ($-$$) db 0

; The magic number that exists at the end of the file denoting that this is the boot sector
dw 0xaa55
