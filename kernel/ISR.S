.macro ISR vec
    .global interruptServiceRoutine\vec
    .type   interruptServiceRoutine\vec, @function
interruptServiceRoutine\vec:
    subq $8, %rsp         # make %rsp 16B-aligned
    pushq %rax            # Push rax to the stack to prevent mangling
    mov    $\vec, %edi    # Pass interrupt index to handleInterrupt as an argument.
    call   handleInterrupt
    popq   %rax
    addq   $8, %rsp
    iretq
.endm

# Generate handler stubs for interrupts 0-31.
.irp vec,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ISR \vec
.endr

# Generate the isr dispatch table for the same set.
.global interruptServiceRoutineTable
interruptServiceRoutineTable:
.irp vec,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    .quad interruptServiceRoutine\vec
.endr
