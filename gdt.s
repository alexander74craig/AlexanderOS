gdtStart:

; GDT null segment descriptor
gdtNull:
	dd 0x0;
	dd 0x0;

; GDT code segment descriptor.
gdtCode:
	dw 0xffff ; Limit (first 16 bits)
	dw 0x0 ; Base (bits 0 -15)
	db 0x0 ; Base (bits 16 -23)
	; [present:1] Is present in memory
	; [privilege:00] Is the highest privilege
	; [descriptor type:1] Is the code or data segment
	; [code:1] Is the code segment
	; [conforming:0] Cannot be accessed by lower privilege segments
	; [readable:1] Can be read
	; [accessed:0] Has not been accessed, this bit is set by a debugger
	db 10011010b
	; [granularity:1] Multiplies the limits by 4k allowing this segments to span 4Gb
	; [32 bit:1] Is 32 bit
	; [64 bit:0] Is not 64 bit code
	; [AVL:0] Unused bit that can be used by our OS, unset
	; [Limit:1111] Last 4 bits of the limit
	db 11001111b
	; [Base:00000000] Last 8 bits of the base
	db 0x0

; GDT data segment descriptor
gdtData:
	dw 0xffff ; Limit (first 16 bits)
	dw 0x0 ; Base (bits 0 -15)
	db 0x0 ; Base (bits 16 -23)
	; [present:1] [privelege:00] [descriptor type:1] 
	; [code:0] Not code, data
	; [expand down:0] 
	; [writable:1] Can be written to
	; [accessed:0]
	db 10010010b
	; [granularity:1] [32 bit:1] [64 bit:0] [AVL:0] [Limit:1111]
	db 11001111b
	; [Base:00000000]
	db 0x0

; Label to mark end of GDT descriptors
gdtEnd:

; GDT descriptor.
gdtDescriptor:
	dw gdtEnd - gdtStart - 1 ; Size of GDT descriptor
	dd gdtStart ; Start address of the GDT

; Offset for the code descriptor from the start of the GDT descriptor
codeSeg equ gdtCode - gdtStart
; Offset for the data descriptor from the start of the GDT descriptor
dataSeg equ gdtData - gdtStart
