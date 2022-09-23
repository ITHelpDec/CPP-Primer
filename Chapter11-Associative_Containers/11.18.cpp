// Exercise 11.18:
/*
 Write the type of map_it from the loop on page 430 without using auto or decltype.
*/

#include <map>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::map<std::string, size_t> word_count = {
        {"man", 1},
        {"bear", 2},
        {"pig", 3},
    };
    
    // get an iterator positiond on the first element
    // auto map_it = word_count.cbegin();
    std::map<std::string, size_t>::const_iterator map_it = word_count.cbegin();

    // compare the current iterator to the off-the-end iterator
    while (map_it != word_count.cend()) {
        // de-reference the iterator to print the element key-value pairs
        std::cout << map_it->first << " occurs " << map_it->second << (map_it->second == 1 ? " time." : " times.") << std::endl;
        ++map_it;
    }
}
