// Exercise 9.42:
/*
 Given that you want to read a character at a time into a string, and you know that you need to read at least 100 characters, how might you improve the performance of your program?
 
 >> word.reserve(30);
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
