// Exercise 11.16:
/*
 Using a map iterator write an expression that assigns a value to an element.
*/

#include <map>
#include <iostream>

int main()
{
    std::map<int, int> imap = {
        { 0, 1 },
        { 2, 3 },
        { 4, 5 },
        { 6, 7 },
        { 8, 9 },
    };
    
    std::map<int, int>::iterator map_iter = imap.begin();
    
    std::cout << "Before value insertions:" << std::endl;
    std::cout << "iamp:";
    for (auto const &e : imap) std::cout << e.first<< " " << e.second << " ";
    std::cout << std::endl;
    
    const int x = 0;
    
    for (map_iter = imap.begin(); map_iter != imap.cend(); ++map_iter) {
        // cannot modify keys
        // map_iter->first = x;
        
        // we can, however, modify values by derefering the .second member of the iterator
        map_iter->second = x;
    }
    
    std::cout << "After value insertions:" << std::endl;
    std::cout << "iamp:";
    for (auto const &e : imap) std::cout << e.first<< " " << e.second << " ";
    std::cout << std::endl;
    
    return 0;
}
