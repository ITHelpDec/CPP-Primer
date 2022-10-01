// Exercise 9.24:
/*
 Write a program that fetches the first element in a vector using at,
 the subscript operator, front, and begin. Test your program on an empty vector.
 */

#include <vector>
#include <iostream>

int main()
{
    // create two vectors - one with elements, one without
    std::vector<int> ivec1 = {0, 1, 2, 3, 4 ,5};
    std::vector<int> ivec2;
    
    // using ivec1, return first element of each vector using
    // at
    std::cout << ivec1.at(0) << std::endl;
    // front
    std::cout << ivec1.front() << std::endl;
    // begin()
    std::cout << *(ivec1.begin()) << std::endl;
    
    //using ivec2...
    // at (out of range)
    // std::cout << ivec2.at(0) << std::endl;
    // front (error)
    // std::cout << ivec2.front() << std::endl;
    // begin() (another error)
    // std::cout << *(ivec2.begin()) << std::endl;
    
    return 0;
}
