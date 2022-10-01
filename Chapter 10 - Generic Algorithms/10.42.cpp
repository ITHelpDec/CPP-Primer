// Exercise 10.42:
/*
 Reimplement the program that eliminated duplicate words that we wrote in § 10.2.3 (p. 383) to use a list instead of a vector.
 
 >> Correction: p 384
*/

#include <vector>
#include <string>
#include <list>
#include <iostream>

void elimDups(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    auto end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());
}

void elimDupsList(std::list<std::string> &sl)
{
    // sort the elements to make duplicates appear next to each other
    sl.sort();
    
    // use unique to remove consecutive duplicates
    sl.unique();
}

int main()
{
    std::vector<std::string> svec = { "man", "bear", "pig", "man", "bear", "pig" };
    std::list<std::string> sl(svec.begin(), svec.end());
    
    std::cout << "svec: ";
    for (const auto &e : svec) std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "sl: ";
    for (const auto &e : sl) std::cout << e << " ";
    std::cout << std::endl;
    
    elimDups(svec);
    elimDupsList(sl);
    
    std::cout << "svec: ";
    for (const auto &e : svec) std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "sl: ";
    for (const auto &e : sl) std::cout << e << " ";
    std::cout << std::endl;
    
    return 0;
}
