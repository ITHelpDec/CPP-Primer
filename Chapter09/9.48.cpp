// Exercise 9.48:
/*
 Given the definitions of name and numbers on page 365, what does numbers.find(name) return?
 
 >> numbers.find(name) will not find the string "r2d2" in numbers, so will return npos (18446744073709551615, or an unsigned -1)
*/

#include <string>
#include <iostream>

int main()
{
    std::string numbers("0123456789"), name("r2d2");
    
    auto pos = numbers.find(name);
    
    if (pos != std::string::npos)
        std::cout << pos << std::endl;
    else
        std::cout << std::string::npos << std::endl;

    return 0;
}
