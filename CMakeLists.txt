cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(AlexanderOS
        LANGUAGES
            ASM
            CXX)

set(CMAKE_CXX_FLAGS "-ffreestanding -Wall -Wextra -fno-rtti -nostdlib -nodefaultlibs -lgcc -fno-exceptions")
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/Boot.ld)
set(CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT}")


file (GLOB cppFiles ./*.cpp)
file (GLOB asmFiles ./*.s)

add_executable(kernel
        ${cppFiles}
        ${asmFiles})
target_include_directories(kernel PUBLIC ${CMAKE_SOURCE_DIR})
