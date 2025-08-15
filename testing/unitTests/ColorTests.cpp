#include "Color.hpp"
#include "UnitTesting.hpp"

TEST(Colortest)
{
    Color testColor{2,2,1};
    ASSERT_EQ(testColor.red, 2);
    ASSERT_EQ(testColor.green, 2);
    ASSERT_EQ(testColor.blue, 1);
    return 0;
}

TEST_LIST(Colortest)