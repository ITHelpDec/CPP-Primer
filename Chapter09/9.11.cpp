// Exercise 9.11:
/*
 Show an example of each of the six ways to create and initialize a vector.
 Explain what values each vector contains.
*/

#include <vector>

std::vector<int> v1;                            // empty vector
std::vector<int> v2(v1);                        // copy of v1
std::vector<int> v3 = v1;                       // copy of v1
std::vector<int> v4 {0, 1, 2};                  // vector that holds 0, 1, 2
std::vector<int> v5 = {0, 1, 2};                // vector that holds 0, 1, 2
std::vector<int> v6(v5.begin(), v5.end())       // vector that holds 0, 1, 2 (starts at 0, ends at 2)


std::vector<int> v7(5);                         // vector containing 7 zero'd elements
std::vector<int> v8(5,1);                       // vector containing 7 elements of "1"
;
