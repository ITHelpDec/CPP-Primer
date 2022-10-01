// Exercise 9.38:
/*
 Write a program to explore how vectors grow in the library you use.
*/

#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::vector<std::string> svec1;
    std::vector<std::string> svec2(24);
    
    std::cout << svec1.size() << " " << svec1.capacity() << std::endl;
    std::cout << svec2.size() << " " << svec2.capacity() << std::endl;
    
    svec2.resize(20);
    
    std::cout << svec2.size() << " " << svec2.capacity() << std::endl;
    
    svec2.shrink_to_fit();
    
    std::cout << svec2.size() << " " << svec2.capacity() << std::endl;
    
    return 0;
}
