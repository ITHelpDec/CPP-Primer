// Exercise 9.41:
/*
 Write a program that initializes a string from a vector<char>.
*/

#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<char> cvec = { 'a', 'b', 'c', 'd', 'e', 'f' };
    
    std::string word;
    for (const auto &e : cvec)
        word.push_back(e);
    
    // could also use the following
    // std::string word(cvec.begin(), cvec.end();
    
    std::cout << word << std::endl;
    
    return 0;
}
