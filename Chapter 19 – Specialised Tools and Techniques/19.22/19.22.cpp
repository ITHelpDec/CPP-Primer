// Exercise 19.22:
/*
 Add a member of type Sales_data to your Token class.
*/

#include "Token.hpp"

int main()
{
    Token t;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    t = 42;
    std::cout << "t: " << t << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    t = 'c';
    std::cout << "t: " << t << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    t = 3.14;
    std::cout << "t: " << t<< "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    t = "manbearpig";
    std::cout << "t: " << t << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Sales_data test case
    t = Sales_data("123-456-789", 5, 125);
    std::cout << "t: " << t << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
