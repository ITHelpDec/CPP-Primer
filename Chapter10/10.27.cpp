// Exercise 10.27:
/*
 In addition to unique (§ 10.2.3, p. 384), the library defines function named unique_copy that takes a third iterator denoting a destination into which to copy the unique elements.
 Write a program that uses unique_copy to copy the unique elements from a vector into an initially empty list.
 
 >> Could probably create a container_print function to keep main() tidier
*/

#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <iterator>

void copy_to_list(const std::vector<int> &ivec, std::list<int> &il)
{
    std::unique_copy(ivec.begin(), ivec.end(), std::back_inserter(il));
}

int main()
{
    // create vector and print results
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5};
    std::cout << "ivec: ";
    for (const auto &e : ivec)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // create empy list and print results
    std::list<int> il;
    std::cout << "il: ";
    for (const auto &e : il)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // perform function
    std::cout << "Copying from ivec to il..." << std::endl;
    copy_to_list(ivec, il);
    
    // print updated results
    std::cout << "il: ";
    for (const auto &e : il)
        std::cout << e << " ";
    std::cout << std::endl;
    return 0;
}
