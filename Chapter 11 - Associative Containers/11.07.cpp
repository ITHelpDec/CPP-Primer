// Exercise 11.07:
/*
 Define a map for which the key is the family’s last name and the value is a vector of the children’s names.
 Write code to add new families and to add new children to an existing family.
*/

#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    // key is string for last name; value is vector of children's names
    std::map<std::string, std::vector<std::string>> family_map;
    
   // create holders for standard input
    std::string first_name, last_name;
    
    // push holders into map
    // wish only example in the book had been clearer
    // ++word_count[word] is like adding the word, and then increasing the size_t by 1 for each match
    // there were a lot of complicated examples online, but this way seemed the most concise
    while (std::cin >> first_name >> last_name) {
        family_map[last_name].push_back(first_name);
    }
    
    // iterate through each key and it associated values
    for (const auto &surname : family_map) {
        std::cout << "Family name: " << surname.first << std::endl;
        std::cout << "Children: ";
        for (const auto &name : surname.second)
            std::cout << name << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
