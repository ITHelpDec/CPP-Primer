// Exercise 11.22:
/*
 Given a map<string, vector<int>>, write the types used as an argument and as the return value for the version of insert that inserts one element.
*/

/*
 Awfully-worded question...if the map is as follows...
 //
 // siv_map.insert({s, ivec}).first->second.push_back(x);
 //
 >> ...then the argument is the pair {s, ivec}, or...
 //
 // std::pair<std::string, std::vector<int>>
 //
 >> ..., whereas the return type of the insert member is an iterator key with a bool value...
 //
 // std::map<std::pair<std::string, std::vector<int>>::iterator, bool>
 //
 >> I have included an example below.
 
 */

#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // create map
    std::map<std::string, std::vector<int>> siv_map;
    
    // create temp variables to store input and results
    std::string s;
    std::vector<int> ivec;
    int x;
    
    // take result for s and x
    while (std::cin >> s >> x)
        // push results into map with shorthand code
        // remember second.push_back() to add associated values to the end to the end of the container
        siv_map.insert({s, ivec}).first->second.push_back(x);
    
    for (const auto &p : siv_map) {
        // std::cout << p.first << " occurs " << p.second << (p.second == 1 ? " time." : " times.") << std::endl;
        std::cout << p.first << ": ";
        for (const auto &e : p.second)
            std::cout << e << " ";
        std::cout << std::endl;
    }
    
    // auto ret = siv_map.insert({s, ivec});
    // std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = siv_map.insert({s, ivec});
    
    std::cout << std::endl;
    
    return 0;
}
