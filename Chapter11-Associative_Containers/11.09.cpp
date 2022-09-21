// Exercise 11.09:
/*
 Define a map that associates words with a list of line numbers on which the word might occur.
*/

#include <map>
#include <string>
#include <list>
#include <iostream>

int main()
{
    std::map<std::string, std::list<int>> words = {
        { "man", { 1, 2, 3 } },
        { "bear", { 4, 5, 6 } },
        { "pig", { 7, 8, 9 } },
    };
    
    for (const auto &e : words) {
        std::cout << e.first << " will likely appear in lines: ";
        for (const auto &f : e.second)
            std::cout << f << " ";
        std::cout << std::endl;
    }
        
    
    return 0;
}
