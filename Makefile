# Configure variables based on host machine
AS= ~/cross/bin/i686-elf-as 
CC= ~/cross/bin/i686-elf-gcc
CXX= ~/cross/bin/i686-elf-g++ 
CXXFLAGS= -ffreestanding -Wall -Wextra -fno-rtti -nostdlib -nodefaultlibs -lgcc -fno-exceptions
ISO_DIR= isodir

# Run as iso rescue image
run: AlexanderOS.iso
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
AlexanderOS.bin : kernel.o Boot.o Boot.ld IDT.o ISR.o VGATextModeBuffer.o BootInformation.o DirectDisplay.o Font.o
	 $(CXX) -T Boot.ld -o AlexanderOS.bin kernel.o Boot.o IDT.o ISR.o BootInformation.o VGATextModeBuffer.o DirectDisplay.o Font.o $(CXXFLAGS) 

# Compiles idt
IDT.o : IDT.cpp
	$(CXX) -c IDT.cpp -o IDT.o $(CXXFLAGS)

# Compiles kernel
kernel.o : kernel.cpp
	$(CXX) -c kernel.cpp -o kernel.o $(CXXFLAGS)

# Assembles boot 
Boot.o : Boot.s
	$(AS) Boot.s -o Boot.o

# Assembles isr 
ISR.o : ISR.s
	$(AS) ISR.s -o ISR.o

# Compiles vga text mode display utility
VGATextModeBuffer.o : VGATextModeBuffer.cpp
	$(CXX) -c VGATextModeBuffer.cpp -o VGATextModeBuffer.o $(CXXFLAGS)

BootInformation.o : BootInformation.cpp
	$(CXX) -c BootInformation.cpp -o BootInformation.o $(CXXFLAGS)

# Direct display utility
DirectDisplay.o : DirectDisplay.cpp 
	$(CXX) -c DirectDisplay.cpp -o DirectDisplay.o $(CXXFLAGS)

# Font
Font.o : Font.s
	$(AS) Font.s -o Font.o

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help *.dis *.dism; \
	rm -r $(ISO_DIR)
