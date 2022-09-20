// Exercise 11.03:
/*
 Write your own version of the word-counting program.
*/

#include <map>
#include <string>
#include <iostream>
#include <set>

int main()
{
    std::map<std::string, std::size_t> word_count;
    std::set<std::string> exclude = { "The", "But", "And", "Or", "And", "A", "the", "but", "and", "or", "and", "a" };
    
    std::string word;
    while (std::cin >> word) {
        // if element not found, find returns off-the-end iterator
        if (exclude.find(word) == exclude.end())
            ++word_count[word];
    }
    
    for (const auto &e : word_count)
        std::cout << e.first << " occurs " << e.second << (e.second == 1 ? " time.\n" : " times.\n");
        
    return 0;
}
