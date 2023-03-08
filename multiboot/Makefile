
# Run
run : all
	qemu-system-x86_64 -kernel AlexanderOS.bin

# All
all : AlexanderOS.bin

# Links together OS
AlexanderOS.bin : kernel.o boot.o
	g++ -T boot.ld -o AlexanderOS.bin -ffreestanding -nostdlib -lgcc boot.o kernel.o

# Compiles kernel
kernel.o : kernel.cpp
	g++ -c kernel.cpp -o kernel.o -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti -nostdlib 

# Assembles boot 
boot.o : boot.s
	as boot.s -o boot.o 

# Cleans the directory by removing any build objects
clean :
	rm *.bin *.o *.iso *.log *.help *.dis