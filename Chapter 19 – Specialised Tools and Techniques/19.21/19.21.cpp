// Exercise 19.21:
/*
 Write your own version of the Token class.
*/

#include "Token.hpp"

int main()
{
    Token t;
    
    t = 42;
    std::cout << "t: " << t << "\n";
    
    t = 'c';
    std::cout << "t: " << t << "\n";
    
    t = 3.14;
    std::cout << "t: " << t << "\n";
    
    t = "manbearpig";
    std::cout << "t: " << t << "\n";
    
    return 0;
}
