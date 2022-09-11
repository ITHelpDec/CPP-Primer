// Exercise 9.25:
/*
 In the program on page 349 that erased a range of elements, what happens if elem1 and elem2 are equal?
 What if elem2 or both elem1 and elem2 are the off-the-end iterator?
 
 >> (1) if elem1 and elem2 are the same, they will delete 1 element
 >> (2) if elem2 is an off-the-end operator it will go to the end, but if both elem1 and elem2 are off-the-end, nothing happens (see below)
 */

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> ivec = {0, 1, 2, 3,4, 5, 6, 7, 8, 9};
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    // if elem1 and elem2 are ivec.end(), nothing changes
    ivec.erase(ivec.end(), ivec.end());
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    return 0;
}


