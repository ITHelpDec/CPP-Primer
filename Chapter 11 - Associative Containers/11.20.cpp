// Exercise 11.20:
/*
 Rewrite the word-counting program from § 11.1 (p. 421) to use insert instead of subscripting.
 Which program do you think is easier to write and read? Explain your reasoning.
*/

#include <string>
#include <map>
#include <iostream>

int main()
{
    std::map<std::string, std::size_t> word_count;

    std::string word;
    while (std::cin >> word) {
        //
        // ++word_count[word];
        //
        auto ret = word_count.insert({word, 1});
        if (!ret.second)
            ++ret.first->second;
        
        // i much prefer the ++word_count{word] syntax; it seems much easier to understand
    }
    
    for (const auto &p : word_count)
        std::cout << p.first << " occurs " << p.second << (p.second == 1 ? " time." : " times.") << std::endl;
    
    return 0;
}
