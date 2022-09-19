// Exercise 10.37:
/*
 Given a vector that has ten elements, copy the elements from positions 3 through 7 in reverse order to a list.
*/

#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

// shorthand function
void print_back_to_front(std::vector<int> &ivec, const int &start_pos, const int &end_pos)
{
    // copy contents in reverse order using start and end positions
    std::list<int> il((ivec.crend() - 1) - end_pos, ivec.crend() - start_pos);
    
    std::cout << "il: ";
    for (const auto &e : il) std::cout << e << " ";
    std::cout << std::endl;
}

// using for loop
int main()
{
    // create vector and list
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::list<int> il;
    
    // print intial contents
    std::cout << "ivec: ";
    for (const auto &e : ivec) std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "il: ";
    for (const auto &e : il) std::cout << e << " ";
    std::cout << std::endl;
    
    // reverse copy elements
    int start_pos = 3, end_pos = 7;
    for (auto iter = (ivec.crend() - 1) - end_pos; iter != ivec.crend() - start_pos; ++iter)
        il.push_back(*iter);
    
    // print updated contents
    std::cout << "ivec: ";
    for (const auto &e : ivec) std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "il: ";
    for (const auto &e : il) std::cout << e << " ";
    std::cout << std::endl;
    
    print_back_to_front(ivec, 3, 7);
    
    return 0;
}
