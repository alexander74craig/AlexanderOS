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

option(BUILD_KERNEL "Build the kernel" ON)
option(BUILD_TESTS "Build tests" OFF)

add_subdirectory(common)

if(BUILD_KERNEL)
    add_subdirectory(kernelDefs)
    add_subdirectory(kernel)
    target_link_libraries(common PUBLIC kernelDefs)
    add_custom_target(AlexanderOS.iso)
    add_dependencies(AlexanderOS.iso kernel)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg)
    add_custom_command(TARGET AlexanderOS.iso
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/grub.cfg ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/grub/grub.cfg
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/kernel/kernel ${CMAKE_CURRENT_BINARY_DIR}/iso/boot/kernel
            COMMAND grub-mkrescue -o AlexanderOS.iso iso)
endif()

if(BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(testing)
endif()




