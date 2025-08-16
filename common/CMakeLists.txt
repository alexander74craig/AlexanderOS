CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(common STATIC
        BootInformation.cpp
        Color.cpp
        DirectDisplayTextBuffer.cpp
        MemoryAllocator.cpp
        TextBuffer.cpp
        VGATextModeBuffer.cpp
        Font.S)
target_link_libraries(common PUBLIC kernelDefs)
set(commonHeaders
        BootInformation.hpp
        Color.hpp
        DirectDisplayTextBuffer.hpp
        MemoryAllocator.hpp
        MemoryAllocatorNode.hpp
        MemoryMapEntry.hpp
        TextBuffer.hpp
        VGATextModeBuffer.hpp)
publicizeHeaders(common PUBLIC commonHeaders)