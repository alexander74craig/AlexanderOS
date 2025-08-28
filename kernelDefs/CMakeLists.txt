CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(kernelDefs STATIC
    stubs.cpp)
set(kernelDefsHeaders
        stddef.h
        stdint.h)
publicizeHeaders(kernelDefs INTERFACE kernelDefsHeaders)
target_compile_options(kernelDefs PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -fno-rtti -ffreestanding -fno-exceptions -fno-threadsafe-statics -mno-red-zone -mcmodel=kernel -fno-use-cxa-atexit -fno-asynchronous-unwind-tables -fno-stack-protector>
        $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -ffreestanding>)
target_link_options(kernelDefs PUBLIC
        -nostdlib
        -lgcc
        -nodefaultlibs)
target_compile_definitions(kernelDefs PUBLIC
        $<$<COMPILE_LANGUAGE:CXX>:BUILD_KERNEL>)