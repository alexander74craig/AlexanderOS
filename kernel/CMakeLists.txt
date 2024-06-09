add_executable(kernel
        Boot.S
        BootInformation.cpp
        Color.cpp
        CPPSupport.cpp
        DirectDisplay.cpp
        Font.S
        GDT.S
        IDT.cpp
        ISR.S
        kernel.cpp
        PhysicalMemoryManager.cpp
        TextBuffer.cpp
        VGATextModeBuffer.cpp)
target_include_directories(kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(kernel
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_options(kernel
        PRIVATE -T${CMAKE_CURRENT_SOURCE_DIR}/Boot.ld)