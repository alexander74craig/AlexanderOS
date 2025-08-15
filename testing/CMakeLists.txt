CMAKE_MINIMUM_REQUIRED(VERSION 3.28.3 FATAL_ERROR)

include(CTest)
enable_testing()

add_library(unitTesting INTERFACE)
set(unitTestingHeaders
        UnitTesting.hpp)
publicizeHeaders(unitTesting INTERFACE unitTestingHeaders)

macro(addUnitTests testName sourceFile libraryName)
    add_executable(${testName}
            ${sourceFile})
    target_link_libraries(${testName}
            ${libraryName}
            unitTesting)
    add_test(NAME ${testName} COMMAND ${testName})
endmacro()

add_subdirectory(unitTests)
