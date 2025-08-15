#pragma once
#include "StandardDefinitions.hpp"

using TestFunction = int(*)();

template<size_t size>
inline int run(TestFunction (&tests)[size])
{
    for (size_t i = 0; i < size; i++)
    {
        const int result = tests[i]();
        if (result != 0)
        {
            return result;
        }
    }
    return 0;
}

#define TEST_LIST(...) int main() { TestFunction tests[] = {__VA_ARGS__}; return run(tests);}
#define TEST(name) int name()
#define ASSERT_EQ(expected, actual) if (expected != actual) {return __LINE__;}
#define ASSERT_TRUE(condition) if (!condition) {return __LINE__;}