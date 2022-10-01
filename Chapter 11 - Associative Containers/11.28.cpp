// Exercise 11.28:
/*
 Define and initialize a variable to hold the result of calling find on a map from string to vector of int.
 */

#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    std::map<std::string, std::vector<int>> sivmap;
    
    std::string s;
    std::vector<int> ivec;
    int x;
    
    while (std::cin >> s >> x)
        sivmap[s].push_back(x);
    
    for (const auto &p : sivmap) {
        std::cout << p.first << ": ";
        for (const auto &v : p.second)
            std::cout << v << " ";
        std::cout << std::endl;
    }
    
    // variable defined and initialised to hold the result of calling find
    auto ret = sivmap.find(s);
    
    std::cout << std::endl;
    
    return 0;
}
