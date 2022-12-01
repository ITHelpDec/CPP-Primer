// Example 16.05:
/*
 Write a template version of the print function from § 6.2.4 (p. 217)...
 that takes a reference to an array and can handle arrays of any size and any element type.
*/

#include <iostream>

void print(int (&arr)[10]) {
    for (auto elem : arr) {
        std::cout << elem << " ";
    } std::cout << std::endl;
}

template <typename T, unsigned N> void templatePrint(T (&arr) [N]) {
    for (const auto &elem : arr) {
        std::cout << elem << " ";
    } std::cout << std::endl;
}

int main()
{
    int    arr1[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int    arr2[4]  = { 0, 1, 2, 3 };
    double arr3[3]  = { 1.0, 2.0, 3.0 };
    char   arr4[4]  = { 'a', 'b', 'c', 'd' };
    
    print(arr1);
    templatePrint(arr1);
    
    // print(arr2); -> "no matching function "
    templatePrint(arr2);
    
    templatePrint(arr3);
    
    templatePrint(arr4);
    
    return 0;
}
