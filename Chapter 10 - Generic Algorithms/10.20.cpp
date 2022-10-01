// Exercise 10.20:
/*
 The library defines an algorithm named count_if. Like find_if.
 This function takes a pair of iterators denoting an input range and a predicate that it applies to each element in the given range.
 count_if returns a count of how often the predicate is true.
 Use count_if to rewrite the portion of our program that counted how many words are greater than length 6.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

std::string make_plural(const std::size_t &sz, const std::string &s1, const std::string &s2)
{
    return sz == 1 ? s1 : s1 + s2;
}

void sixes(const std::vector<std::string> &svec, const std::size_t &sz)
{
    int count = 0;
    
    // produces expected result from three strings, but maybe a little sloppy with [&]?
    std::for_each(svec.begin(), svec.end(), [&] (const std::string &s) { return s.size() > sz ? ++count : 0; } );
    
    //print results
    std::cout << count << " " << make_plural(count, "word", "s") << " larger than " << sz << " characters." << std::endl;
}



int main()
{
    std::vector<std::string> svec1 = { "Humpty", "Dumpty", "sat", "on", "a", "wall", "Humpty", "Dumpty", "had", "a", "great", "fall", "all", "the", "king's", "horses", "and", "all", "the", "king's", "men", "couldn't", "put", "Humpty", "together", "again" };
    std::vector<std::string> svec2 = { "manbearbig" };
    std::vector<std::string> svec3;
    
    sixes(svec1, 6);
    sixes(svec2, 6);
    sixes(svec3, 6);
    
    return 0;
}
