// Exercise 10.06:
/*
 Using fill_n, write a program to set a sequence of int values to 0.
*/

#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    // create blank vector
    std::vector<int> ivec;
    
    // set a sequence of int values to 0
    std::fill_n(std::back_inserter(ivec), 10, 0);
    
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    return 0;
}
