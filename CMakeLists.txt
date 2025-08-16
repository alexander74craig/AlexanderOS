cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


project(AlexanderOS
        LANGUAGES
            ASM
            CXX)

add_subdirectory(cmake)

add_subdirectory(testing)

add_subdirectory(kernelDefs)

add_subdirectory(common)

add_subdirectory(kernel)

add_custom_target(AlexanderOS.iso)
add_dependencies(AlexanderOS.iso kernel)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg)
add_custom_command(TARGET AlexanderOS.iso
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/kernel ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/kernel
        COMMAND grub-mkrescue -o AlexanderOS.iso iso)
