interruptServiceRoutine0:
    mov $0, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine1:
    mov $1, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine2:
    mov $2, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine3:
    mov $3, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine4:
    mov $4, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine5:
    mov $5, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine6:
    mov $6, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine7:
    mov $7, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine8:
    mov $8, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine9:
    mov $9, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine10:
    mov $10, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine11:
    mov $11, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine12:
    mov $12, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine13:
    mov $13, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine14:
    mov $14, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine15:
    mov $15, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine16:
    mov $16, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine17:
    mov $17, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine18:
    mov $18, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine19:
    mov $19, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine20:
    mov $20, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine21:
    mov $21, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine22:
    mov $22, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine23:
    mov $23, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine24:
    mov $24, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine25:
    mov $25, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine26:
    mov $26, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine27:
    mov $27, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine28:
    mov $28, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine29:    
    mov $29, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine30:
    mov $30, %eax
    push %eax
    call handleInterrupt
    iret
interruptServiceRoutine31:
    mov $31, %eax
    push %eax
    call handleInterrupt
    iret
.global interruptServiceRoutineTable
interruptServiceRoutineTable:
    .long interruptServiceRoutine0
    .long interruptServiceRoutine1
    .long interruptServiceRoutine2
    .long interruptServiceRoutine3
    .long interruptServiceRoutine4
    .long interruptServiceRoutine5
    .long interruptServiceRoutine6
    .long interruptServiceRoutine7
    .long interruptServiceRoutine8
    .long interruptServiceRoutine9
    .long interruptServiceRoutine10
    .long interruptServiceRoutine11
    .long interruptServiceRoutine12
    .long interruptServiceRoutine13
    .long interruptServiceRoutine14
    .long interruptServiceRoutine15
    .long interruptServiceRoutine16
    .long interruptServiceRoutine17
    .long interruptServiceRoutine18
    .long interruptServiceRoutine19
    .long interruptServiceRoutine20
    .long interruptServiceRoutine21
    .long interruptServiceRoutine22
    .long interruptServiceRoutine23
    .long interruptServiceRoutine24
    .long interruptServiceRoutine25
    .long interruptServiceRoutine26
    .long interruptServiceRoutine27
    .long interruptServiceRoutine28
    .long interruptServiceRoutine29
    .long interruptServiceRoutine30
    .long interruptServiceRoutine31
