// Exercise 10.11:
/*
 Write a program that uses stable_sort and isShorter to sort a vector passed to your version of elimDups.
 Print the vector to verify that your program is correct.
 
 >> std::sort =
 >> a on the sat all and put had men wall fall again great king's Dumpty horses Humpty together couldn't
 >> std::stable_sort
 >> a on all and had men put sat the fall wall again great Dumpty Humpty horses king's couldn't together
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

bool isShorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
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
    std::stable_sort(svec.begin(), svec.end(), isShorter);
    end_unique = std::unique(svec.begin(), svec.end());
    svec.erase(end_unique, svec.end());
}

int main()
{
    // create example vector of ints
    std::vector<std::string> svec = { "Humpty", "Dumpty", "sat", "on", "a", "wall", "Humpty", "Dumpty", "had", "a", "great", "fall", "all", "the", "king's", "horses", "and", "all", "the", "king's", "men", "couldn't", "put", "Humpty", "together", "again" };
    
    std::cout << "ivec: ";
    for (const auto &e : svec)
        std::cout << e << " ";
    std::cout << std::endl << std::endl;
    
    // run function
    std::cout << "Removing duplicates..." << std::endl << std::endl;;
    elimDups(svec);
    
    // use stable sort
    std::stable_sort(svec.begin(), svec.end(), isShorter);
    
    // check results
    std::cout << "Printing new results...\n\nivec: ";
    for (const auto &e : svec)
        std::cout << e << " ";
    std::cout << std::endl << std::endl;
    
    return 0;
}
