CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Prevent GoogleTest from overriding your compiler/linker options
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

macro(addTests testName sourceFile libraryName)
    add_executable(${testName}
            ${sourceFile})
    target_link_libraries(${testName}
            ${libraryName}
            GTest::gtest
            GTest::gtest_main)
    gtest_discover_tests(${testName})
endmacro()

add_subdirectory(unitTests)
