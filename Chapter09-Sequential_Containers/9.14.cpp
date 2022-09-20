// Exercise 9.14:
/*
 Write a program to assign the elements from a list of char* pointers
 to C-style character strings to a vector of strings.
*/

#include <list>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    // create a list of char* pointers to C-style character strings
    std::list<const char*> clist {"big", "bad", "wolf"};
    
    // create a vector container of strings
    std::vector<std::string> svec;
    
    // use assign to assign the elements from the list to the vector
    svec.assign(clist.begin(), clist.end());
    for (auto &e : svec)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    return 0;
}
