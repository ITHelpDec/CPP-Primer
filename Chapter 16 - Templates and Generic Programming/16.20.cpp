// Exercise 16.20:
/*
 Rewrite the function from the previous exercise to use iterators returned from begin and end to control the loop.
*/

#include <iostream>
#include <vector>
#include <list>
#include <unordered_set>
#include <string>

// very little difference to range for loop, but useful
template <typename T> void printContainer(const T &c) {
    for (auto it = c.begin(); it != c.end(); ++it) {
        std::cout << *it << " ";
    } std::cout << std::endl;
}

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
