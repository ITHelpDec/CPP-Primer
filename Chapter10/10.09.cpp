// Exercise 10.07:
/*
 Implement your own version of elimDups.
 Test your program by printing the vector after you read the input, after the call to unique, and after the call to erase.
*/

#include <vector>
#include <algorithm>
#include <iostream>

void elimDups(std::vector<int> &ivec)
{
    // self explanatory sot
    std::sort(ivec.begin(), ivec.end());
    
    // brings uniqe variables to the front
    // returns an iterator position for when the unique operators stop
    auto end_unique = std::unique(ivec.begin(), ivec.end());
    
    // erases from when the unique elements stop
    ivec.erase(end_unique, ivec.end());
}

int main()
{
    // create example vector of ints
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 0, 1, 5, 2, 3, 4 };
    std::cout << "ivec: ";
    for (const auto &e : ivec)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // run function
    std::cout << "Removing duplicates..." << std::endl;
    elimDups(ivec);
    
    // check results
    std::cout << "Printing new results...\nivec: ";
    for (const auto &e : ivec)
        std::cout << e << " ";
    std::cout << std::endl;
    
    return 0;
}
