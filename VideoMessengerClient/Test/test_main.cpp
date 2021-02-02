#include <string>

#include <gtest/gtest.h>

class FirstTest : public ::testing::Test
{
};

TEST_F(FirstTest, simple)
{
    int uno = 1;
    int unoDos = 1;
    EXPECT_EQ(uno, unoDos);

    sleep(10);
}

TEST_F(FirstTest, empty)
{
    std::string res = "";

    EXPECT_EQ(res, "");
    sleep(10);
}
