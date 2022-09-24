// Exercise 11.24:
/*
 What does the following program do?
 
 map<int, int> m;
 m[0] = 1;
 
 */

#include <map>
#include <iostream>

int main()
{
    // creates empty map of key int and value int
    std::map<int, int> m = {
        {0,0}
    };
    
    // check for "0" as a key in map
    // if it exists, change the existing value to 1,
    // if it doesn't exist, create the pair {0,1}
    m[0] = 1;
    
    for (const auto &p : m)
        std::cout << p.first << " " << p.second << std::endl;
    
    return 0;
}
