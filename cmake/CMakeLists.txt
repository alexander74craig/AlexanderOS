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

