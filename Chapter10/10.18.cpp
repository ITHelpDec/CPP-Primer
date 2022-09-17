// Exercise 10.18:
/*
 Rewrite biggies to use partition instead of find_if.
 We described the partition algorithm in exercise 10.13 in § 10.3.1 (p. 387).
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

std::string make_plural(const std::size_t &sz, const std::string &s1, const std::string &s2)
{
    return sz == 1 ? s1 : s1 + s2;
}

void elimDups(std::vector<std::string> &svec)
{
    // first pass
    std::stable_sort(svec.begin(), svec.end());
    auto end_unique = std::unique(svec.begin(), svec.end());
    svec.erase(end_unique, svec.end());
    
    // second pass with lambda
    std::stable_sort(svec.begin(), svec.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); });
    end_unique = std::unique(svec.begin(), svec.end());
    svec.erase(end_unique, svec.end());
}

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz)
{
    elimDups(words);
    
    std::stable_sort(words.begin(), words.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); } );
    
    // auto wc = std::find_if(words.begin(), words.end(), [sz] (const std::string &s) { return s.size() >= sz; } );
    /*
     "The library defines an algorithm named partition that takes a predicate and partitions the container so that values for which the predicate is true appear in the first part and those for which the predicate is false appear in the second part.
     The algorithm returns an iterator just past the last element for which the predicate returned true."
     Just changed the >= to < in this example
     */
    auto wc = std::partition(words.begin(), words.end(), [sz] (const std::string &s) { return s.size() < sz; } );
    
    auto count = words.end() - wc;
    
    std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer:" << std::endl;
    
    // print words of the given size or longer, each one followed by a space
    std::for_each(wc, words.end(), [] (const std::string &s) { std::cout << s << " "; } );
    
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
