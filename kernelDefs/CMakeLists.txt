CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(kernelDefs STATIC
        CPPSupport.cpp)
set(kernelDefsHeaders
        stddef.h
        stdint.h)
publicizeHeaders(kernelDefs PUBLIC kernelDefsHeaders)
target_compile_options(kernelDefs PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -fno-rtti -ffreestanding -fno-exceptions>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -ffreestanding>)
target_link_options(kernelDefs PUBLIC
        -nostdlib
        -lgcc
        -nodefaultlibs)