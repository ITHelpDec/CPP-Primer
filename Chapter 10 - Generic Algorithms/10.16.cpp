// Exercise 10.16:
/*
 Write your own version of the biggies function using lambdas.
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
    // first pass with standard sort (explanation below)
    std::stable_sort(svec.begin(), svec.end());
    
    // create iterator for end of unique elements
    auto end_unique = std::unique(svec.begin(), svec.end());
    
    // erases from when the unique elements stop
    svec.erase(end_unique, svec.end());
    
    // did second pass based on word length because duplicates were still appearing
    std::stable_sort(svec.begin(), svec.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); });
    end_unique = std::unique(svec.begin(), svec.end());
    svec.erase(end_unique, svec.end());
}

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz)
{
    // put words in alphabetical order and remove duplicates
    elimDups(words);
    
    // sort words by size, but maintain alphabetical order for words of the same size
    std::stable_sort(words.begin(), words.end(), [] (const std::string &s1, const std::string &s2) { return s1.size() < s2.size(); } );
    
    // get an iterator to the first element whose .size() is >= sz
    auto wc = std::find_if(words.begin(), words.end(), [sz] (const std::string &s) { return s.size() >= sz; } );
    
    // compute the number of elements with size >= sz
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
