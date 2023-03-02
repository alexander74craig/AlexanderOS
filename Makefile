# Run
run : all
	qemu-system-x86_64 -drive format=raw,file=AlexanderOS.bin,if=floppy

# All
all : AlexanderOS.bin

# AlexanderOS
AlexanderOS.bin : bootSector.bin kernel.bin
	cat bootSector.bin kernel.bin > AlexanderOS.bin

# Kernel binary
kernel.bin : kernelEntryPoint.o kernel.o
	~/cross/bin/i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

# Kernel object file
kernel.o : kernel.cpp
	~/cross/bin/i686-elf-g++ -c $^ -o $@ -ffreestanding

# Kernel entry point object file
kernelEntryPoint.o : kernelEntryPoint.s
	nasm $^ -f elf -o $@

# Boot sector
bootSector.bin : bootSector.s gdt.s loadKernel.s printString.s printStringReal.s protectedMode.s
	nasm bootSector.s -f bin -o bootSector.bin

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help