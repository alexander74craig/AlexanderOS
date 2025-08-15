CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)



add_subdirectory(kernel)

add_executable(main
        Boot.S
        GDT.S
        ISR.S
        IDT.cpp
        main.cpp)
target_include_directories(main
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_options(main
        PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/Boot.ld)
target_link_libraries(main PUBLIC kernel kernelFlags)
