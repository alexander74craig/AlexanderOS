CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_executable(kernel
        Boot.S
        GDT.S
        ISR.S
        IDT.cpp
        kernel.cpp)
target_include_directories(kernel
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_options(kernel
        PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/Boot.ld)
target_link_libraries(kernel PUBLIC common)
