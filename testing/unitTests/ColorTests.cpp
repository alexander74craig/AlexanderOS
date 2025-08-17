#include "Color.hpp"
#include "gtest/gtest.h"

TEST(Color, constructor)
{
    Color testColor{2,2,1};
    ASSERT_EQ(testColor.red, 2);
    ASSERT_EQ(testColor.green, 2);
    ASSERT_EQ(testColor.blue, 1);
}