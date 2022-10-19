// Exercise 14.37:
/*
 Write a class that tests whether two values are equal.
 Use that object and the library algorithms to write a program to replace all instances of a given value in a sequence.
*/

#include <iostream>
#include <algorithm>
#include <vector>

class TestEqual {
    
public:
    // assign input to test variable
    TestEqual(int x) : test(x) { }
    
    // take input and compare to test to return bool for predicate
    bool operator() (const int &input) { return input == test; }
    
private:
    int test;
};

void print_vec(std::ostream &os, const std::vector<int> &ivec)
{
    for (const auto &e : ivec) {
        os << e << " ";
    } std::cout << std::endl;
}

int main()
{
    std::cout << "The vector is as follows:\n";
    std::vector<int> ivec = { 0, 1, 9, 3, 4, 5 };
    print_vec(std::cout, ivec);
    std::cout << std::endl;
    
    // check input is correct and in vector
    std::cout << "What number would you like to replace?: ";
    int out;
    if ((!(std::cin >> out)) || (std::find(ivec.begin(), ivec.end(), out) == ivec.end()))
    { std::cout << "Bad input / number not found – closing programme..." << std::endl; return -1; }
    
    // take input for replacement
    std::cout << "What would you like to replace it with?: ";
    int in;
    if (!(std::cin >> in))
    { std::cout << "Bad input - closing programme..." << std::endl; return -1; }
    
    // std::replace_if()
    // iterate through container
    // where predicate is true, replace with new value
    std::replace_if(ivec.begin(), ivec.end(), TestEqual(out), in);
    
    //
    // TestEqual test9(9);
    // std::replace_if(ivec.begin(), ivec.end(), test9, in);
    //
    
    print_vec(std::cout, ivec);

    return 0;
}
