gdt_start:

; GDT null segment descriptor.
gdt_null:
	dd 0x0;
	dd 0x0;

; GDT code segment descriptor.
gdt_code:
	dw 0xffff ; Limit (first 16 bits)
	dw 0x0 ; Base (bits 0 -15)
	db 0x0 ; Base (bits 16 -23)
	; [present:1] Is present in memory.
	; [privilege:00] Is the highest privilege.
	; [descriptor type:1] Is the code or data segment.
	; [code:1] Is the code segment.
	; [conforming:0] Cannot be accessed by lower privilege segments.
	; [readable:1] Can be read.
	; [accessed:0] Has not been accessed, this bit is set by a debugger.
	db 10011010b
	; [granularity:1] Multiplies the limits by 4k allowing this segments to span 4Gb.
	; [32 bit:1] Is 32 bit.
	; [64 bit:0] Is not 64 bit code.
	; [AVL:0] Unused bit that can be used by our OS, unset.
	; [Limit:1111] Last 4 bits of the limit.
	db 11001111b
	; [Base:00000000] Last 8 bits of the base.
	db 0x0

; GDT data segment descriptor.
gdt_data:
	dw 0xffff ; Limit (first 16 bits)
	dw 0x0 ; Base (bits 0 -15)
	db 0x0 ; Base (bits 16 -23)
	; [present:1] [privelege:00] [descriptor type:1] 
	; [code:0] Not code, data. 
	; [expand down:0] 
	; [writable:1] Can be written to.
	; [accessed:0]
	db 10010010b
	; [granularity:1] [32 bit:1] [64 bit:0] [AVL:0] [Limit:1111]
	db 11001111b
	; [Base:00000000]
	db 0x0

; Label to mark end of GDT descriptors.
gdt_end:

; GDT descriptor.
gdt_descriptor:
	dw gdt_end - gdt_start - 1 ; Size of GDT descriptor.
	dd gdt_start ; Start address of the GDT

; Offset for the code descriptor from the start of the GDT descriptor.
CODE_SEG equ gdt_code - gdt_start
; Offset for the data descriptor from the start of the GDT descriptor.
DATA_SEG equ gdt_data - gdt_start
