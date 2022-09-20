// Exercise 10.13:
/*
 The library defines an algorithm named partition that takes a predicate and partitions the container so that values for which the predicate is true appear in the first part and those for which the predicate is false appear in the second part.
 The algorithm returns an iterator just past the last element for which the predicate returned true.
 Write a function that takes a string and returns a bool indicating whether the string has five characters or more.
 Use that function to partition words.
 Print the elements that have five or more characters.
*/

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

// function checks if string has 5 characters or more
bool morethanfive(const std::string &s)
{
    return s.size() > 4;
}

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

void print(const std::vector<std::string> &svec)
{
    for (const auto &e : svec)
        std::cout << e << " ";
    std::cout << std::endl;
}

void fives(std::vector<std::string> &svec)
{
    // remove duplicates (double pass)
    std::sort(svec.begin(), svec.end());
    auto words_unique = std::unique(svec.begin(), svec.end());
    svec.erase(words_unique, svec.end());
    std::stable_sort(svec.begin(), svec.end(), isShorter);
    words_unique = std::unique(svec.begin(), svec.end());
    svec.erase(words_unique, svec.end());
    
    // create iterator for words not greater than 4 chars
    auto words_partition = std::partition(svec.begin(), svec.end(), morethanfive);
    
    // erase words 4 or less
    svec.erase(words_partition, svec.end());
    
    // tidy up the end result (filter by size, hten alphabetical order)
    std::sort(svec.begin(), svec.end());
    std::stable_sort(svec.begin(), svec.end(), isShorter);
}

int main()
{
    std::vector<std::string> svec = { "Humpty", "Dumpty", "sat", "on", "a", "wall", "Humpty", "Dumpty", "had", "a", "great", "fall", "all", "the", "king's", "horses", "and", "all", "the", "king's", "men", "couldn't", "put", "Humpty", "together", "again" };
    
    std::cout << "svec: \n";
    print(svec);
    
    fives(svec);
    
    std::cout << "\n\nString with 5 characters of more: \n";
    print(svec);
    
    return 0;
}
