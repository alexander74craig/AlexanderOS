.section .text.bootentry
.code16 # Sets the code to 16 bit instructions
# Sets the offset for memory to where this file is loaded into memory by BIOS
.set kernelOffset, 0x1000 # Memory location to load the kernel at

mov %dl, (bootDrive) # Reads boot drive into memory


# Notifies user that the kernel is being loaded
mov $loadingKernelMessage, %bx  
call printStringReal
call loadKernel


# Notifies the user and switches to protected mode
mov $pmSwitchMessage , %bx 
call printStringReal
call switchToPm

# Halt prevents accidental execution of included files
jmp .
.include "loadKernel.s"
.include "printStringReal.s"
.include "gdt.s"
.include "printString.s"
.include "protectedMode.s"

.code32
pmExitPoint: # Exit point for switch_to_pm after registers are invalidated

mov  $pmSuccessMessage, %ebx
call printString

call kernelOffset # Jump to kernelEntryPoint.s as loaded into memory.

jmp . # Hold position after all else is done

# Messages for various execution points.
loadingKernelMessage:
    .asciz "Loading kernel. "
pmSwitchMessage:
    .asciz "Switching to protected mode. "
pmSuccessMessage: 
    .asciz "Successfully switched to protected mode."

# Location to store drive number of the boot drive
bootDrive:
     .byte 0
