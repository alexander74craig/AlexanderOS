CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

add_library(kernel STATIC
        BootInformation.cpp
        Color.cpp
        CPPSupport.cpp
        DirectDisplayTextBuffer.cpp
        MemoryAllocator.cpp
        TextBuffer.cpp
        VGATextModeBuffer.cpp
        Font.S)
target_link_libraries(kernel PUBLIC kernelFlags)
set(kernelHeaders
        BootInformation.hpp
        Color.hpp
        DirectDisplayTextBuffer.hpp
        MemoryAllocator.hpp
        MemoryAllocatorNode.hpp
        MemoryMapEntry.hpp
        TextBuffer.hpp
        VGATextModeBuffer.hpp
        StandardDefinitions.hpppp)
publicizeHeaders(kernel PUBLIC kernelHeaders)