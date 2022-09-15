// Exercise 10.01:
/*
 The algorithm header defines a function named count that, like find, takes a pair of iterators and a value.
 count returns a count of how often that value appears.
 Read a sequence of ints into a vector and print the count of how many elements have a given value.
 
 >> Would be interesting to write a version that doesn't duplicate results
*/

#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    // create empty vector to store integer input
    std::vector<int> ivec; // = { 2, 5, 6, 2, 4, 6, 7, 2 };
    int number = 0;
    
    // take input until eof
    while (std::cin >> number)
        ivec.push_back(number);
    
    std::cout << std::endl;
    
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    for (const auto &e : ivec)
        std::cout << e << " appears " << std::count(ivec.begin(), ivec.end(), e) << " time(s)." << std::endl;
    
    return 0;
}
