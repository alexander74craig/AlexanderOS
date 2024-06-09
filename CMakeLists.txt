cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(AlexanderOS
        LANGUAGES
            ASM
            CXX)

set(CMAKE_CXX_FLAGS "-ffreestanding -Wall -Wextra -fno-rtti -nostdlib -nodefaultlibs -lgcc -fno-exceptions")


add_subdirectory(kernel)

add_custom_target(AlexanderOS.iso)
add_dependencies(AlexanderOS.iso kernel)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg)
add_custom_command(TARGET AlexanderOS.iso
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/kernel/kernel ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/kernel
        COMMAND grub-mkrescue -o AlexanderOS.iso iso
        COMMAND qemu-system-x86_64 -boot d -cdrom AlexanderOS.iso)
