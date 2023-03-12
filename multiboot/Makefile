# Configure variables based on host machine
AS= ~/cross/bin/i686-elf-as 
CC= ~/cross/bin/i686-elf-gcc
CXX= ~/cross/bin/i686-elf-g++ 
CXXFLAGS= -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib -lgcc -nodefaultlibs
ISO_DIR= isodir

# Run
run : all
	qemu-system-x86_64 -kernel AlexanderOS.bin

# Run as iso rescue image
runIso : all
	qemu-system-x86_64 -boot d -cdrom AlexanderOS.iso

# All
all : AlexanderOS.iso

# Creates grub rescue image file
AlexanderOS.iso : AlexanderOS.bin
	mkdir -p $(ISO_DIR)/boot/grub; \
	cp AlexanderOS.bin $(ISO_DIR)/boot/AlexanderOS.bin; \
	cp grub.cfg $(ISO_DIR)/boot/grub/grub.cfg; \
	grub-mkrescue -o AlexanderOS.iso $(ISO_DIR)

# Links together OS
AlexanderOS.bin : kernel.o boot.o
	 $(CXX) -T boot.ld -o AlexanderOS.bin boot.o kernel.o $(CXXFLAGS)

# Compiles kernel
kernel.o : kernel.cpp
	$(CXX) -c kernel.cpp -o kernel.o $(CXXFLAGS)

# Assembles boot 
boot.o : boot.s
	$(AS) boot.s -o boot.o

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help *.dis ; \
	rm -r $(ISO_DIR)