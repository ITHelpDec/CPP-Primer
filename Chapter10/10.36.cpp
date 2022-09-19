// Exercise 10.36:
/*
 Use find to find the last element in a list of ints with value 0.
 
 >> Difficult to return exact position within list compared to using vectors
 >> Could potentially copy the list into a vector...
*/

#include <list>
#include <iostream>

int main()
{
    // result should be ivec[7]
    std::list<int> il = { 1, 2, 3, 4, 5, 0, 6, 7, 8, 9 };
    
    std::cout << "il: ";
    for (const auto &e : il) std::cout << e << " ";
    std::cout << std::endl;
    
    auto last_zero = std::find(il.rbegin(), il.rend(), 0);

    std::cout << *last_zero << " was found just before " << *last_zero.base() << "." << std::endl;
    
    return 0;
}
