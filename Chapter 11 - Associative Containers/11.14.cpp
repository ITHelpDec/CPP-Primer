// Exercise 11.14:
/*
 Extend the map of children to their family name that you wrote for the exercises in § 11.2.1 (p. 424) by having the vector store a pair that holds a child’s name and birthday.
*/

#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    // std::map<std::string, std::vector<std::string>> family_map;
    std::map<std::string, std::vector<std::pair<std::string, std::string>>> family_map;
    
    // std::string first_name, last_name;
    std::string first_name, last_name, birthday;
    
    //
    // while (std::cin >> first_name >> last_name) {
    //     family_map[last_name].push_back(first_name);
    // }
    //
    
    while (std::cin >> first_name >> last_name >> birthday)
        family_map[last_name].push_back({ first_name, birthday });
    
    // iterate through each key and it associated values
    for (const auto &surname : family_map) {
        std::cout << "Family name: " << surname.first << std::endl;
        std::cout << "Children: ";
        
        //
        // for (const auto &name : surname.second)
        //     std::cout << name << " ";
        // std::cout << std::endl;
        //
        
        // I used C++17 decomposition declarations to print pair from map value
        for (const auto &[name, birthday] : surname.second)
            std::cout << name << " (" << birthday << ")" << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
