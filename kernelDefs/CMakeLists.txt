CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(kernelDefs INTERFACE)
set(kernelDefsHeaders
        stddef.h
        stdint.h)
publicizeHeaders(kernelDefs INTERFACE kernelDefsHeaders)
target_compile_options(kernelDefs INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -fno-rtti -ffreestanding -fno-exceptions -fno-threadsafe-statics>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -ffreestanding>)
target_link_options(kernelDefs INTERFACE
        -nostdlib
        -lgcc
        -nodefaultlibs)
target_compile_definitions(kernelDefs INTERFACE
        $<$<COMPILE_LANGUAGE:CXX>:BUILD_KERNEL>)