// Exercise 11.23:
/*
 Rewrite the map that stored vectors of children’s names with a key that is the family last name for the exercises in § 11.2.1 (p. 424) to use a multimap.
 
 >> Multimap .insert always adds a new key regardless of whether it exists or not, so if else statements were used to add the children's names to any already-existing family names
 
*/

#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    // key is string for last name; value is vector of children's names
    // std::map<std::string, std::vector<std::string>> family_map;
    std::multimap<std::string, std::vector<std::string>> family_map;
    
   // create string and vector holders for standard input
    std::string last_name, first_name;
    std::vector<std::string> first_name_vec;
    
    // take first name and surname as standard input
    while (std::cin >> first_name >> last_name) {
        // check if surname already exists in multimap
        if (family_map.find(last_name) == family_map.end()) {
            // if it exists, then add first name to vector
            family_map.find(last_name)->second.push_back(first_name);
        } else {
            // if it doesn't exist then create a new key-value pair and add first name to the vector
            family_map.insert({last_name, {first_name_vec}})->second.push_back(first_name);
        }
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
