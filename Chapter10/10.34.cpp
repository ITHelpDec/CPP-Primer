// Exercise 10.34:
/*
 Use reverse_iterators to print a vector in reverse order.
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
    for (auto r_iter = ivec.crbegin(); r_iter != ivec.crend(); ++r_iter)
        std::cout << *r_iter << " ";
    std::cout << std::endl;
    
    return 0;
}
