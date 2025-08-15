CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

macro(publicizeHeaders target targetType targetHeaders)
    list(TRANSFORM ${targetHeaders}
            PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
    target_include_directories(${target}
            ${targetType}
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
    set_target_properties(${target}
            PROPERTIES
            PUBLIC_HEADER "${${targetHeaders}}")
endmacro()

add_library(kernelFlags INTERFACE)
target_compile_options(kernelFlags INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -fno-rtti -ffreestanding -fno-exceptions>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -ffreestanding>)
target_link_options(kernelFlags INTERFACE
        -nostdlib
        -lgcc
        -nodefaultlibs)