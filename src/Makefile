# Configure variables based on host machine
AS= ~/cross/bin/i686-elf-as 
CC= ~/cross/bin/i686-elf-gcc
CXX= ~/cross/bin/i686-elf-g++ 
CXXFLAGS= -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -lgcc -nodefaultlibs
ISO_DIR= isodir

# Run
run : AlexanderOS.bin
	qemu-system-x86_64 -kernel AlexanderOS.bin

# Run as iso rescue image
runIso : AlexanderOS.iso
	qemu-system-x86_64 -boot d -cdrom AlexanderOS.iso

# Run iso in bochs
runBochs : AlexanderOS.iso
	bochs

# All
all : AlexanderOS.iso

# Creates grub rescue image file
AlexanderOS.iso : AlexanderOS.bin
	mkdir -p $(ISO_DIR)/boot/grub; \
	cp AlexanderOS.bin $(ISO_DIR)/boot/AlexanderOS.bin; \
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg; \
	grub-mkrescue -o AlexanderOS.iso $(ISO_DIR)

# Links together OS
AlexanderOS.bin : kernel.o boot.o isr.o idt.o
	 $(CXX) -T boot.ld -o AlexanderOS.bin  $^ $(CXXFLAGS)

# Compiles idt
idt.o : idt.cpp
	$(CXX) -c idt.cpp -o idt.o $(CXXFLAGS)

# Compiles kernel
kernel.o : kernel.cpp
	$(CXX) -c kernel.cpp -o kernel.o $(CXXFLAGS)

# Assembles boot 
boot.o : boot.s
	$(AS) boot.s -o boot.o

# Assembles isr 
isr.o : isr.s
	$(AS) isr.s -o isr.o

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help *.dis *.dism; \
	rm -r $(ISO_DIR)

isr.o : isr.s
	$(AS) isr.s -o isr.o