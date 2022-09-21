// Exercise 11.12:
/*
 Write a program to read a sequence of strings and ints, storing each into a pair.
 Store the pairs in a vector.
*/

#include <string>
#include <utility>
#include <vector>
#include <iostream>

int main()
{
    std::vector<std::pair<std::string, int>> vipair;
    
    std::string s;
    int i;
    
    while (std::cin >> s >> i) {
        vipair.push_back(std::make_pair(s, i));
    }
    
    //
    // can also perform the following with curly braces - potentially cleaner
    //
    // while (std::cin >> s >> i) {
    //     vipair.push_back({ s, i });
    // }
    
    for (const auto &e : vipair)
        std::cout << "| " << e.first << " " << e.second << " |";
    
    std::cout << std::endl;
    
    return 0;
}
