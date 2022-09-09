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


// ---- parametrised testing with customised log report labels (selection sort)----
/* 
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
INSTANTIATE_TEST_SUITE_P  // instantiation of parametrised test
(
    SelectionSortParamTest,  // instantiation name
    SelectionSortTestLabelled,  // test suite name
    testing::ValuesIn(inputMap),  // parameter generator (notice 'ValuesIn' not 'Values')
    // lambda invoked as name/label generator for log report output
    [](const testing::TestParamInfo<SelectionSortTestLabelled::ParamType>& info){ return info.param.first; }
);
 */


///////////////////////////////////////////////////////////////////////////////


// ---- parametrised testing with customised log report labels (multiple sort implementations) ----
std::map< std::string, std::function<void(std::vector<int>&)> >funcMap  // map of function objects for sort algorithms
{
    {"SelectionSort", Sorts::SelectionSort},
    {"BubbleSort", Sorts::BubbleSort}
};
std::map<std::string, std::vector<int>> inputMap  // map of input types to be tested
{
    {"Empty", {}},
    {"SingleElement", {4}},
    {"TypicalSmall", {5,3,1,7,8}},
    {"ReverseSorted", {5,4,3,2,1}},
    {"DuplicateElement", {5,3,1,5,8}}
};

class SortsTestLabelled : public testing::TestWithParam<
    std::tuple<  // accessed via get<element_index>(tuple)
        std::pair< const std::string, std::function<void(std::vector<int>&)> >,
        std::pair< const std::string, std::vector<int> >
    >
> {};

INSTANTIATE_TEST_SUITE_P  // instantiation of parametrised test
(
    SortsParamTest,  // instantiation name
    SortsTestLabelled,  // test suite name
    // parameter generator, creates all possible combinations of passed parameters
    testing::Combine(testing::ValuesIn(funcMap), testing::ValuesIn(inputMap)), 
    // lambda invoked as name/label generator for log report output
    [](const testing::TestParamInfo<SortsTestLabelled::ParamType>& info)
    { 
        return std::get<0>(info.param).first + "_" +  // algorithm part of the label
                std::get<1>(info.param).first;   // input type part of the label
    }
);
TEST_P(SortsTestLabelled, InputSizes)  // parametrised test
{
    auto params = GetParam();
    auto SortFunction = std::get<0>(params).second;  // function object extracted from map value of 1st element of tuple
    auto input = std::get<1>(params).second, expected{input};  // input type extracted from map value of 2nd element of tuple
    SortFunction(input);  // invoke the function object (SelectionSort / BubbleSort) with the input type
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(input, expected);
}


// ---- gtest driver code ----
int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}