// Exercise 11.31:
/*
 Write a program that defines a multimap of authors and their works.
 Use find to find an element in the multimap and erase that element.
 Be sure your program works correctly if the element you look for is not in the map.
 */

#include <map>
#include <string>
#include <vector>
#include <iostream>

std::ostream &print_map(std::ostream &os, const std::multimap<std::string, std::vector<std::string>> &svmap)
{
    for (const auto &p : svmap) {
        os << p.first << ": ";
        for (const auto &v : p.second)
            os << v << ", ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return os;
}

int main()
{
    std::multimap<std::string, std::vector<std::string>> works = {
        { "Barth, John", { "Sot-Weed Factor", "Lost in the Funhouse" } },
        { "J K Rowling", { "Harry Potter" } }
    };
    
    std::cout << ".:. Current authors and their works .:. " << std::endl;
    print_map(std::cout, works);
    
    std::string test = "Barth, John";
    
    std::cout << "Attempting to delete " << test << "...\n" << std::endl;
    auto search = works.find(test);
    if (search != works.end())
        works.erase(search);
    else
        std::cerr << "Author not in the list";
    
    std::cout << ".:. Updated authors and their works .:. " << std::endl;
    print_map(std::cout, works);
    
    std::cout << "Attempting to delete " << test << " again...\n" << std::endl;
    search = works.find(test);
    if (search != works.end())
        works.erase(search);
    else
        std::cerr << "!!! Author not in the list !!!\n" << std::endl;
    
    std::cout << ".:. Final verison of authors and their works .:. " << std::endl;
    print_map(std::cout, works);
    
    return 0;
}


#inc
