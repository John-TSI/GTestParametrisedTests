#include"../inc/sorts.hpp"


// helper function for sorting algorithms below
void Sorts::Swap(int* a, int* b)
{
    int tmp{*a};
    *a = *b;
    *b = tmp;
}

// simple implementation of selection sort algorithm
void Sorts::SelectionSort(std::vector<int>& vec)
{
    int idx_min, n = vec.size();
    for(int i{0}; i<n-1; ++i)
    {
        idx_min = i;
        for(int j{i+1}; j<n; ++j)
        {
            if(vec[j] < vec[idx_min]){ idx_min = j; }
        }
        if(idx_min != i){ Sorts::Swap(&vec[idx_min], &vec[i]); }
    }
}

// simple implementation of bubblesort algorithm
void Sorts::BubbleSort(std::vector<int>& vec)
{   int n = vec.size();
    bool sorted{false};
    do
    {
        sorted = true;
        for(int i{0}; i<n-1; ++i)
        {
            if(vec[i+1] < vec[i])
            { 
                Sorts::Swap(&vec[i+1], &vec[i]); 
                sorted = false; 
            }
        }
    } while(!sorted);
}