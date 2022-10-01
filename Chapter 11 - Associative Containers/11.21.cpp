// Exercise 11.21:
/*
 Assuming word_count is a map from string to size_t and word is a string, explain the following loop:
 while (cin >> word)
 ++word_count.insert({word, 0}).first->second;
*/

#include <map>
#include <string>
#include <iostream>

int main()
{
    std::map<std::string, std::size_t> word_count;
    
    std::string word;
    while (std::cin >> word)
        ++word_count.insert({word, 0}).first->second;
    
        // this line is a cleaner, albeit busier version of the following:
        //
        // (1) auto ret = word_count.insert({word, 0});
        // (2) if (!ret.second)
        // (3)    ++ret.first->second;
        //
    
    for (const auto &p : word_count)
        std::cout << p.first << " occurs " << p.second << (p.second == 1 ? " time." : " times.") << std::endl;
    
    return 0;
}
