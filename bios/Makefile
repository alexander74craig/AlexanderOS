

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
	ld -o kernel.bin -Ttext 0x1000 kernelEntryPoint.o kernel.o --oformat binary

# Kernel object file
kernel.o : kernel.cpp
	g++ -c kernel.cpp -o kernel.o -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti

# Kernel entry point object file
kernelEntryPoint.o : kernelEntryPoint.s
	as kernelEntryPoint.s -o kernelEntryPoint.o

# Boot sector binary.
bootSector.bin : bootSector.o
	ld -T bootSector.ld  --oformat binary -o bootSector.bin bootSector.o

# Boot sector object file
bootSector.o : bootSector.s gdt.s loadKernel.s printString.s printStringReal.s protectedMode.s
	as bootSector.s -o bootSector.o

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help *.dis