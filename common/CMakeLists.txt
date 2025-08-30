CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(common STATIC
        BootInformation.cpp
        Color.cpp
        DirectRGBTextBuffer.cpp
        MemoryAllocator.cpp
        TextBuffer.cpp
        EGATextBuffer.cpp
        Font.S
        CPPSupport.cpp
        Memory.cpp
        SerialTextBuffer.cpp
        CPUID.cpp)
set(commonHeaders
        BootInformation.hpp
        Color.hpp
        DirectRGBTextBuffer.hpp
        MemoryAllocator.hpp
        MemoryAllocatorNode.hpp
        TextBuffer.hpp
        EGATextBuffer.hpp
        FrameBuffer.hpp
        Memory.hpp
        SerialTextBuffer.hpp
        CPUID.hpp)
publicizeHeaders(common PUBLIC commonHeaders)