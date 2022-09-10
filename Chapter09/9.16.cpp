// Exercise 9.16:
/*
 Repeat the previous program, but compare elements in a list<int> to a vector<int>.
*/

#include <list>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> ilist = {0, 1, 2, 3, 4};
    std::vector<int> ivec = {0, 1, 2, 3, 4};
    
    if (ilist == ivec) {
        std::cout << "ilist and ivec are equal" << std::endl;
        std::cout << "Each element is equal, and they both share the same size()." << std::endl;
    }
    else {
        std::cout << "ilist and ivec are not equal" << std::endl;
        std::cout << "Either one or more of the elements are not the same, or they have a different size()." << std::endl;
    }
    
    return 0;
}
