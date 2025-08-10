add_executable(kernel
        Boot.S
        BootInformation.cpp
        Color.cpp
        CPPSupport.cpp
        DirectDisplayTextBuffer.cpp
        Font.S
        GDT.S
        IDT.cpp
        ISR.S
        kernel.cpp
        TextBuffer.cpp
        VGATextModeBuffer.cpp
        MemoryAllocator.cpp
        MemoryMapEntry.h)
target_include_directories(kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(kernel
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_options(kernel
        PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/Boot.ld)