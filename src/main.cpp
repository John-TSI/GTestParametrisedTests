#include<iostream>
#include"../inc/sorts.hpp"


// printer function
void PrintVec(std::vector<int>& vec)
{
    std::cout << '{';
    for(int i{0}; i<vec.size(); ++i)
    {
        (i == vec.size()-1) ? std::cout << vec[i] : std::cout << vec[i] << ',';
    }
    std::cout << "}\n";
}

int main(int argc, char** argv)
{
    std::vector<int> vec1{5,3,1,7,8};
    std::cout << "From main:\n";
    std::cout << "SelectionSort: {5,3,1,7,8} --> ";
    Sorts::SelectionSort(vec1);
    PrintVec(vec1);

    vec1 = {5,3,1,7,8};
    std::cout << "BubbleSort: {5,3,1,7,8} --> ";
    Sorts::BubbleSort(vec1);
    PrintVec(vec1);

    return 0;
}