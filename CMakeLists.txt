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

add_subdirectory(src)

add_custom_target(AlexanderOS.iso)
add_dependencies(AlexanderOS.iso main)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg)
add_custom_command(TARGET AlexanderOS.iso
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/src/main ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/main
        COMMAND grub-mkrescue -o AlexanderOS.iso iso)
