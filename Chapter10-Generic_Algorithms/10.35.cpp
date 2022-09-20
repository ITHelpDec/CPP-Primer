// Exercise 10.35:
/*
 Now print the elements in reverse order using ordinary iterators.
*/

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    
    std::cout << "ivec: ";
    for (const auto &e : ivec) std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "reversed: ";
    for (auto iter = ivec.cend() - 1; iter != ivec.cbegin() - 1; --iter)
        std::cout << *iter << " ";
    std::cout << std::endl;
    
    return 0;
}
