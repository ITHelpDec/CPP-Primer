// Exercise 9.15:
/*
 Write a program to determine whether two vector<int>s are equal.
*/

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v1 = {0, 1, 2, 3, 4};
    std::vector<int> v2 = {0, 1, 2, 3, 4};
    
    if (v1 == v2) {
        std::cout << "v1 and v2 are equal" << std::endl;
        std::cout << "Each element is equal, and they both share the same size()." << std::endl;
    }
    else {
        std::cout << "v1 and v2 are not equal" << std::endl;
        std::cout << "Either one or more of the elements are not the same, or they have a different size()." << std::endl;
    }
    
    return 0;
}
