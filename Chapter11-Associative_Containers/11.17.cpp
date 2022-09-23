// Exercise 11.19:
/*
 Assuming c is a multiset of strings and v is a vector of strings, explain the following calls.
 
 Indicate whether each call is legal:
 
 copy(v.begin(), v.end(), inserter(c, c.end()));
 copy(v.begin(), v.end(), back_inserter(c));
 copy(c.begin(), c.end(), inserter(v, v.end()));
 copy(c.begin(), c.end(), back_inserter(v));
 
*/

#include <algorithm>
#include <vector>
#include <iterator>
#include <iostream>

// function to print results
std::ostream &print(std::ostream &os, const std::vector<int> &ivec, const std::vector<int> &c)
{
    std::cout << "ivec: ";
    for (const auto &e : ivec) os << e << " ";
    std::cout << std::endl;
    
    std::cout << "c: ";
    for (const auto &e : c) os << e << " ";
    std::cout << std::endl;
    
    return os;
}

void one(const std::vector<int> &ivec, std::vector<int> c)
{
    std::cout << "\ninserter: \n";
    std::copy(ivec.cbegin(),ivec.cend(), inserter(c, c.end()));
    print(std::cout, ivec, c);
}

void two(const std::vector<int> &ivec, std::vector<int> c)
{
    std::cout << "\nback_inserter: \n";
    std::copy(ivec.cbegin(), ivec.cend(), std::back_inserter(c));
    print(std::cout, ivec, c);
}

void three(std::vector<int> &ivec, const std::vector<int> c)
{
    std::cout << "\ninserter: \n";
    std::copy(c.cbegin(), c.cend(), inserter(ivec, ivec.end()));
    print(std::cout, ivec, c);
}

void four(std::vector<int> &ivec, const std::vector<int> c)
{
    std::cout << "\ninserter: \n";
    std::copy(c.cbegin(), c.cend(), inserter(ivec, ivec.end()));
    print(std::cout, ivec, c);
}



int main()
{
    // create test variables
    std::vector<int> ivec =  { 0, 1, 2, 3, 4, 5 ,6, 7, 8, 9 };
    std::vector<int> c;
    
    std::cout << "initial values: \n";
    print(std::cout, ivec, c);
    
    // (1)
    // inserts elements from ivec into c
    one(ivec, c);
    
    // (2)
    // inserts elements from
    two(ivec, c);
    
    // (3)
    three(ivec, c);
    
    // (4)
    four(ivec, c);
    
    std::cout << std::endl;
    
    return 0;
}
