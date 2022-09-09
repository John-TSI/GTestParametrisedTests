#include<gtest/gtest.h>
#include<algorithm>
#include"../inc/sorts.hpp"


TEST(SortingTests, InputSizes)
{
    std::vector<std::vector<int>> inputs
    {
        {},  // empty
        {4},  // single element
        {5,3,1,7,8},  // typical small input
        {5,4,3,2,1},  // reverse sorted
        {5,3,1,5,8}  // input with duplicate element
    };

    for(auto input : inputs)
    {
        auto expected{input};
        Sorts::SelectionSort(input);
        std::sort(expected.begin(), expected.end());
        EXPECT_EQ(input, expected);
    }
}

// gtest driver code
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}