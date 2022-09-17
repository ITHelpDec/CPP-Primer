// Exercise 10.22:
/*
 Rewrite the program to count words of size 6 or less using functions in place of the lambdas.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <ostream>

void vprint(const std::vector<std::string> &svec)
{
    for (const auto &e : svec)
        std::cout << e << " ";
    std::cout << std::endl;
}

std::string make_plural(const size_t &sz, const std::string &s1, const std::string &s2)
{
    return sz == 1 ? s1 : s1 + s2;
}

void elim_dups(std::vector<std::string> &svec)
{
    std::sort(svec.begin(), svec.end());
    auto unique_begin = std::unique(svec.begin(), svec.end());
    svec.erase(unique_begin, svec.end());
    // std::stable_sort(svec.begin(), svec.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); } );
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

bool atleastsize(const std::string &s, const std::string::size_type &sz)
{
    return s.size() <= sz;
}

std::ostream &print(std::ostream &os, const std::string &s, char &c)
{
    return os << s << c;
}

void biggies(std::vector<std::string> &svec, std::vector<std::string>::size_type sz)
{
    elim_dups(svec);
    
    // #1
    // std::stable_sort(words.begin(), words.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); } );
    std::stable_sort(svec.begin(), svec.end(), isShorter);
    
    // #2
    // create iterator point from when element size is greater than "sz"
    // use std::bind to pull "sz" from biggies() parameter list to put it into another function i.e. atleastsize
    auto wc = std::stable_partition(svec.begin(), svec.end(), std::bind(atleastsize, std::placeholders::_1, sz));
    
    // count is distance between wc and end of container
    auto count = wc - svec.begin();
    
    std::cout << count << " " << make_plural(count, "word", "s") << " of at least " << sz << make_plural(sz, " character", "s") << " found:" << std::endl;
    
    // #3
    // print words of the given size or longer, each one followed by a space
    // std::for_each(svec.begin(), wc, [] (const std::string &s) { std::cout << "\"" << s << "\" "; } );
    
    // this was the hardest part of removing the lambda functions
    // the book provides the following code on page 400:
    // for_each(svec.begin(), wc, std::bind(print, std::ref(os), std::placeholders::_1, ’ ’));
    // ..., which is misleading: "os" needs to be "std::cout" in order to work (won't work without std::ref)
    std::for_each(svec.begin(), wc, std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));
    
    std::cout << std::endl;
}
int main()
{
    std::vector<std::string> words = { "Humpty", "Dumpty", "sat", "on", "a", "wall", "Humpty", "Dumpty", "had", "a", "great", "fall", "all", "the", "king's", "horses", "and", "all", "the", "king's", "men", "couldn't", "put", "Humpty", "together", "again" };
    std::vector<std::string> mbp = { "man", "bearpig" };
    std::vector<std::string> empty;
    
    std::cout << std::endl;
    
    biggies(words, 6);
    biggies(mbp, 6);
    biggies(empty, 6);
    
    return 0;
}
