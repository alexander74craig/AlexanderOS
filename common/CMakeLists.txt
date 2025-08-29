CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(common STATIC
        BootInformation.cpp
        Color.cpp
        DirectDisplayTextBuffer.cpp
        MemoryAllocator.cpp
        TextBuffer.cpp
        VGATextModeBuffer.cpp
        Font.S
        CPPSupport.cpp
        Memory.cpp
        SerialTextBuffer.cpp)
set(commonHeaders
        BootInformation.hpp
        Color.hpp
        DirectDisplayTextBuffer.hpp
        MemoryAllocator.hpp
        MemoryAllocatorNode.hpp
        TextBuffer.hpp
        VGATextModeBuffer.hpp
        FrameBuffer.hpp
        Memory.hpp
        SerialTextBuffer.hpp)
publicizeHeaders(common PUBLIC commonHeaders)