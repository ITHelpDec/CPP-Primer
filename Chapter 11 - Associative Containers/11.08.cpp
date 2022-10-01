// Exercise 11.08:
/*
 Write a program that stores the excluded words in a vector instead of in a set. What are the advantages to using a set?
*/

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

int main()
{
    std::map<std::string, std::size_t> word_count;
    std::vector<std::string> excluded_words = { "the", "but", "and", "or", "an", "a", "The", "But", "And", "Or", "An", "A" };
    
    std::string word;
    while (std::cin >> word) {
        // if element not found, find returns off-the-end iterator
        auto found = std::find(excluded_words.begin(), excluded_words.end(), word);
        if (found == excluded_words.end())
            ++word_count[word];
    }
    
    for (const auto &e : word_count)
        std::cout << e.first << " occurs " << e.second << (e.second == 1 ? " time.\n" : " times.\n");
        
    return 0;
}
