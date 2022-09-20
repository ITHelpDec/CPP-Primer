// Exercise 9.13:
/*
 How would you initialize a vector<double> from a list<int>?
 From a vector<int>?
 Write code to check your answers.
*/

#include <vector>
#include <list>
#include <iostream>

int main()
{
    
    std::list<int> lint = {0, 1, 2, 3, 4};
    std::cout << "lint contains the following elements: ";
    for (auto &e : lint)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    std::cout << "dvec contains the following elements: ";
    std::vector<double> dvec(lint.begin(), lint.end());
    for (auto &e : dvec)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    std::cout << "ivec contains the following elements: ";
    std::vector<int> ivec(lint.begin(), lint.end());
    for (auto &e : ivec)
        std::cout << e << " ";
    
    std::cout << std::endl;
}
