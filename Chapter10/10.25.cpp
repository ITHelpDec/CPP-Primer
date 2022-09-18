// Exercise 10.25:
/*
 In the exercises for § 10.3.2 (p. 392) you wrote a version of biggies that uses partition.
 Rewrite that function to use check_size and bind.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>

std::string make_plural(const std::size_t &sz, const std::string &s1, const std::string &s2)
{
    return sz == 1 ? s1 : s1 + s2;
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

bool check_size(const std::string &s, const std::string::size_type &sz)
{
    return sz > s.size();
}

void elimDups(std::vector<std::string> &svec)
{
    // first pass
    std::stable_sort(svec.begin(), svec.end());
    auto end_unique = std::unique(svec.begin(), svec.end());
    svec.erase(end_unique, svec.end());
}

std::ostream &print(std::ostream &os, const std::string &s, const char &c)
{
    return os << s << c;
}

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz)
{
    // get rid of duplicates
    elimDups(words);
    
    // use a std::bind of stable_sort to tidy up the list
    std::stable_sort(words.begin(), words.end(), std::bind(isShorter,std::placeholders::_1,std::placeholders::_2));
    
    // re-write partition function to use check_size and bind
    // auto wc = std::partition(words.begin(), words.end(), [sz] (const std::string &s) { return s.size() < sz; } );
    // check_size(const std::string &s, conststd::string::size_type sz)
    // const std::string &s             – native to check_size function
    // const std::string::size_type sz  – native from local function "biggies)
    auto wc = std::partition(words.begin(), words.end(), std::bind(check_size,std::placeholders::_1, sz));
    
    auto count = words.end() - wc;
    
    std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer:" << std::endl;
    
    // used std::bind for &print ostream
    std::for_each(wc, words.end(), std::bind(print, std::ref(std::cout), std::placeholders::_1, ' '));
    
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> svec1 = { "Humpty", "Dumpty", "sat", "on", "a", "wall", "Humpty", "Dumpty", "had", "a", "great", "fall", "all", "the", "king's", "horses", "and", "all", "the", "king's", "men", "couldn't", "put", "Humpty", "together", "again" };
    std::vector<std::string> svec2 = { "manbearbig" };
    std::vector<std::string> svec3;
    
    biggies(svec1, 5);
    biggies(svec2, 5);
    biggies(svec3, 5);
    
    return 0;
}
