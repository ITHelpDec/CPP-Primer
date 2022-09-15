// Exercise 10.03:
/*
 Use accumulate to sum the elements in a vector<int>.
*/

#include <vector>
#include <numeric> // "accumulate" belongs to the numeric library
#include <iostream>

int main()
{
    // create vector of ints
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 5 };
    
    // accumulate into sum
    int sum = std::accumulate(ivec.begin(), ivec.end(), 0);
    
    // output results
    std::cout << sum << std::endl;
    
    return 0;
}
