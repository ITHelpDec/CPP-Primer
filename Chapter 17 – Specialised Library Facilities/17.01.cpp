// Exercise 17.01:
/*
 Define a tuple that holds three int values and initialize the members to 10, 20, and 30.
*/

#include <tuple>
#include <iostream>

int main()
{
    std::tuple<int, int, int> it(10, 20, 30);
    
    std::cout << "it: ";
    std::cout << std::get<0>(it) << ", ";
    std::cout << std::get<1>(it) << ", ";
    std::cout << std::get<2>(it) << std::endl;
    
    return 0;
}
