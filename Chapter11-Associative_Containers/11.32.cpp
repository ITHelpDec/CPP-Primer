// Exercise 11.32:
/*
 Using the multimap from the previous exercise, write a program to print the list of authors and their works alphabetically.
*/

#include <map>
#include <string>
#include <vector>
#include <iostream>

// Below I have used a temporary vector to sort the values with each key before printing to std::ostream
std::ostream &print_map_sorted(std::ostream &os, const std::multimap<std::string, std::vector<std::string>> &svmap)
{
    // iterate through keys and push to std::ostream
    for (const auto &p : svmap) {
        os << p.first << ": ";
        
        // being mindful of scope, create a temporary vector to hold the values of each key for sorting
        std::vector<std::string> v_copy;
        // iterate through values and add to temporary vector
        for (const auto &v : p.second)
            v_copy.push_back(v);
        // sort temporary vector
        std::sort(v_copy.begin(), v_copy.end());
        // push contents of sorted vector to std::ostream
        for (const auto &e : v_copy)
            os << e << ", ";
        
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    return os;
}

int main()
{
    // multimap set up with values deliverately in not ascending order
    std::multimap<std::string, std::vector<std::string>> works = {
        { "Barth, John", { "Sot-Weed Factor", "Lost in the Funhouse" } },
        { "J K Rowling", { "Harry Potter 3", "Harry Potter 2", "Harry Potter 1" } },
        { "John McClane", { "Die Hard 3", "Die Hard 2", "Die Hard 1" } }
    };
    
    std::cout << ".:. Current authors and their works .:. " << std::endl;
    print_map_sorted(std::cout, works);
    
    std::string test = "Barth, John";
    
    std::cout << "Attempting to delete " << test << "...\n" << std::endl;
    auto search = works.find(test);
    if (search != works.end())
        works.erase(search);
    else
        std::cerr << "Author not in the list";
    
    std::cout << ".:. Updated authors and their works .:. " << std::endl;
    print_map_sorted(std::cout, works);
    
    std::cout << "Attempting to delete " << test << " again...\n" << std::endl;
    search = works.find(test);
    if (search != works.end())
        works.erase(search);
    else
        std::cerr << "!!! Author not in the list !!!\n" << std::endl;
    
    std::cout << ".:. Final verison of authors and their works .:. " << std::endl;
    print_map_sorted(std::cout, works);
    
    return 0;
}
