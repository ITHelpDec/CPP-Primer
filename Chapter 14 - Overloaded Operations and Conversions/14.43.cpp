// Exercise 14.43:
/*
 Using library function objects, determine whether a given int value is divisible by any element in a container of ints.
*/

#include <functional>
#include <utility>
#include <vector>
#include <iostream>

int main()
{
    std::vector<int> ivec = { 2, 3, 5 };
    std::cout << "ivec: ";
    for (const auto &e : ivec) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    // std::modulus<> will return "false", where "lhs % rhs"
    // we swap the std::placeholder::_1 position about within std::modulus<>, such that we now calculate "rhs % lhs"
    // e.g. 7 % 2 == 1 (true), 7 % 3 == 1 (true), 7 % 5 == 1 (true), which would return an iterator of the first result using std::find()
    // we, however, want the opposite, so we can choose std::find_if_not()
    // if our search reaches ivec.end(), then "rhs % lhs == 0" was not achieved
    // we can then safely assume this number is not divisible by an element in the vector and print accordingly
    
    std::cout << "\nTesting function from 2 to 20...\n";
    for (auto i = 2; i != 21; ++i) {
        std::cout << i << " is "<<
        (std::find_if_not(ivec.begin(), ivec.end(), std::bind(std::modulus<int>(), i, std::placeholders::_1)) == ivec.end() ? "not ": "") <<
        "divisible by a vector element." << std::endl;
    }
    
    return 0;
}
