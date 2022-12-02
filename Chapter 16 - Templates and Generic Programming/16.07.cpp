// Example 16.07:
/*
 Write a constexpr template that returns the size of a given array.
*/

#include <iostream>

template <typename T, std::size_t N>constexpr std::size_t arraySize(T (&arr) [N]) { return N; }

int main()
{
    int arr1[] = { 1, 2, 3, 4 };
    int arr2[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
    
    std::cout << "arr1 has " << arraySize(arr1) << " elements." << std::endl;
    std::cout << "arr2 has " << arraySize(arr2) << " elements." << std::endl;
    
    return 0;
}
