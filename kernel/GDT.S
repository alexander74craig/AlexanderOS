.align 8
gdtStart:

# GDT null segment descriptor
gdtNull:
	.word 0x0
	.word 0x0
	.word 0x0
	.word 0x0

# GDT code segment descriptor.
gdtCode32:
	.word 0xffff # Limit (first 16 bits)
	.word 0x0 # Base (bits 0 -15)
	.byte 0x0 # Base (bits 16 -23)
	# [present:1] Is present in memory
	# [privilege:00] Is the highest privilege
	# [descriptor type:1] Is the code or data segment
	# [code:1] Is the code segment
	# [conforming:0] Cannot be accessed by lower privilege segments
	# [readable:1] Can be read
	# [accessed:0] Has not been accessed, this bit is set by a debugger
	.byte 0b10011010
	# [granularity:1] Multiplies the limits by 4k allowing this segment to span 4Gb
	# [32 bit:1] Is not 32 bit
	# [64 bit:0] Is 64 bit code
	# [AVL:0] Unused bit that can be used by our OS, unset
	# [Limit:1111] Last 4 bits of the limit
	.byte 0b11001111
	# [Base:00000000] Last 8 bits of the base
	.byte 0x0

# GDT code segment descriptor.
gdtCode:
	.word 0xffff # Limit (first 16 bits)
	.word 0x0 # Base (bits 0 -15)
	.byte 0x0 # Base (bits 16 -23)
	# [present:1] Is present in memory
	# [privilege:00] Is the highest privilege
	# [descriptor type:1] Is the code or data segment
	# [code:1] Is the code segment
	# [conforming:0] Cannot be accessed by lower privilege segments
	# [readable:1] Can be read
	# [accessed:0] Has not been accessed, this bit is set by a debugger
	.byte 0b10011010
	# [granularity:1] Multiplies the limits by 4k allowing this segment to span 4Gb
	# [32 bit:0] Is not 32 bit
	# [64 bit:1] Is 64 bit code
	# [AVL:0] Unused bit that can be used by our OS, unset
	# [Limit:1111] Last 4 bits of the limit
	.byte 0b10101111
	# [Base:00000000] Last 8 bits of the base
	.byte 0x0

# GDT data segment descriptor
gdtData:
	.word 0xffff # Limit (first 16 bits)
	.word 0x0 # Base (bits 0 -15)
	.byte 0x0 # Base (bits 16 -23)
	# [present:1] [privilege:00] [descriptor type:1]
	# [code:0] Not code, data
	# [expand down:0] 
	# [writable:1] Can be written to
	# [accessed:0]
	.byte 0b10010010
	# [granularity:1] [32 bit:1] [64 bit:0] [AVL:0] [Limit:1111]
	.byte 0b11001111
	# [Base:00000000]
	.byte 0x0

# Label to mark end of GDT descriptors
gdtEnd:

# GDT descriptor.
gdtDescriptor:
	.word gdtEnd - gdtStart - 1 # Size of GDT descriptor
	.long gdtStart # Start address of the GDT
.global gdtDescriptor
# Offset for the code descriptor from the start of the GDT descriptor
.set codeSeg32, gdtCode32 - gdtStart
.global codeSeg32
.set codeSeg,  gdtCode - gdtStart
.global codeSeg
codeSegSelector: .word codeSeg
.global codeSegSelector
# Offset for the data descriptor from the start of the GDT descriptor
.set dataSeg,  gdtData - gdtStart
.global dataSeg
