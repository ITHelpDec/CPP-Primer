// Exercise 14.34:
/*
 Define a function-object class to perform an if-then-else operation:
 The call operator for this class should take three parameters.
 It should test its first parameter and if that test succeeds, it should return its second parameter;
 otherwise, it should return its third parameter.
*/

#include <iostream>
#include <string>

class IfThenElse {
public:
    
    // takes a string to check against password
    bool operator() (const std::string &s, bool t, bool f);
    
private:
    std::string password = "manbearpig";
};

bool IfThenElse::operator() (const std::string &s, bool t, bool f) { return s == password ? t : f; }

int main()
{
    std::string s;
    std::cout << "PLease enter a password: ";
    std::cin >> s;
    
    IfThenElse login;
    
    // implicit pass to login.operator()
    std::cout << ( login(s, true, false) ? "Correct" : "Incorrect" ) << std::endl;
    
    // explicit pass
    // std::cout << ( login.operator() (s, true, false) ? "Correct" : "Incorrect" ) << std::endl;
    
    return 0;
}
