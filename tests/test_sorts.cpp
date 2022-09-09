// based on tutorial: https://www.youtube.com/watch?v=JJqRlSTQlh4

#include<gtest/gtest.h>
#include<algorithm>
#include<string>
#include"../inc/sorts.hpp"


// ---- sharing test logic for multiple inputs ----
/* 
TEST(SelectionSortTest, InputSizes)
{
    std::vector<std::vector<int>> inputs
    {
        {},  // empty input
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

TEST(BubbleSortTest, InputSizes)
{
    std::vector<std::vector<int>> inputs
    {
        {},  // empty input
        {4},  // single element
        {5,3,1,7,8},  // typical small input
        {5,4,3,2,1},  // reverse sorted
        {5,3,1,5,8}  // input with duplicate element
    };

    for(auto input : inputs)
    {
        auto expected{input};
        Sorts::BubbleSort(input);
        std::sort(expected.begin(), expected.end());
        EXPECT_EQ(input, expected);
    }
} 
*/


///////////////////////////////////////////////////////////////////////////////


// ---- parametrised testing (selection sort)----
/* 
class SelectionSortTest : public testing::TestWithParam<std::vector<int>> {};
TEST_P(SelectionSortTest, InputSizes)  // parametrised test
{
    auto input = GetParam(), expected{input};
    Sorts::SelectionSort(input);
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(input, expected);
}
INSTANTIATE_TEST_SUITE_P  // instantiation of parametrised test (inputs supplied after test definition)
(
    SelectionSortParamTest,  // instantiation name
    SelectionSortTest,  // test suite name
    testing::Values  // parameter generator
    (
        std::vector<int>{},  // empty input
        std::vector<int>{4},  // single element
        std::vector<int>{5,3,1,7,8},  // typical small input
        std::vector<int>{5,4,3,2,1},  // reverse sorted
        std::vector<int>{5,3,1,5,8}  // input with duplicate element
    )
);
*/


///////////////////////////////////////////////////////////////////////////////


// ---- parametrised testing with customised log labels (selection sort)----
std::map<std::string, std::vector<int>> inputMap
{
    {"Empty", {}},
    {"SingleElement", {4}},
    {"TypicalSmall", {5,3,1,7,8}},
    {"ReverseSorted", {5,4,3,2,1}},
    {"DuplicateElement", {5,3,1,5,8}}
};
class SelectionSortTestLabelled : public testing::TestWithParam<
    std::pair<const std::string, std::vector<int>> > {};
TEST_P(SelectionSortTestLabelled, InputSizes)  // parametrised test
{
    auto input = GetParam().second, expected{input};
    Sorts::SelectionSort(input);
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(input, expected);
}
INSTANTIATE_TEST_SUITE_P  // instantiation of parametrised test (inputs supplied after test definition)
(
    SelectionSortParamTest,  // instantiation name
    SelectionSortTestLabelled,  // test suite name
    testing::ValuesIn(inputMap),  // parameter generator (notice 'ValuesIn' not 'Values')
    // lambda invoked as name/label generator for log output
    [](const testing::TestParamInfo<SelectionSortTestLabelled::ParamType>& info){ return info.param.first; }
);


// ---- gtest driver code ----
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}