// Exercise 11.04:
/*
 Extend your program to ignore case and punctuation.
 For example, “example.” “example,” and “Example” should all increment the same counter.
*/

#include <map>
#include <string>
#include <iostream>
#include <set>

int main()
{
    // set up empty word_count map
    std::map<std::string, std::size_t> word_count;
    
    // set up exclusions list
    std::set<char> include_alphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    std::set<char> exclude_uppercase = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
    
    // read standard input until eof
    std::string word;
    while (std::cin >> word) {
        // partition letters and non-letters, then erase from when the non-letters start
        auto punctuation_starts = std::remove_if(word.begin(), word.end(), [&] (auto &e) { return include_alphabet.find(e) == include_alphabet.end(); } );
        word.erase(punctuation_starts, word.end());
        
        // loop through elements of string: if uppercase, change to lowercase
        for (auto &e : word) {
            if (exclude_uppercase.find(e) != exclude_uppercase.end())
                e += 32;
        }
        
        // add the final product to our word count
        ++word_count[word];
    }
    
    for (const auto &e : word_count)
        std::cout << e.first << " occurs " << e.second << (e.second == 1 ? " time.\n" : " times.\n");
        
    return 0;
}
