// Exercise 16.19:
/*
 Write a function that takes a reference to a container and prints the elements in that container. Use the container’s size_type and size members to control the loop that prints the elements.
 
 >> Did this in earlier exercise
*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <string>

template <typename T> void printContainer(const T &c) {
    for (const auto &e : c) {
        std::cout << e << " ";
    } std::cout << std::endl;
}

// could also do ::size_type, but then we would be restricted to random-access containers
// template <typename T> void printContainer(const T &c) {
//     for (template T::size_type i = 0; i != c.size(); ++i) {
//         std::cout << c[i] << " ";
//     } std::cout << std::endl;
// }

int main()
{
    std::vector<int> ivec = { 0, 1, 2, 3, 4 };
    printContainer(ivec);
    
    std::list<char> clist = { 'a', 'b', 'c' };
    printContainer(clist);
    
    std::unordered_set<std::string> usset = { "man", "bear", "pig" };
    printContainer(usset);
    
    return 0;
}
