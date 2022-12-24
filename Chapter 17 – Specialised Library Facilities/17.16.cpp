// Exercise 17.16:
/*
 What would happen if your regex object in the previous program were initialized with "[^c]ei"?
 Test your program using that pattern to see whether your expectations were correct.
 
 >> My assumption was that it would only work for the two-character string "ei"
 >> The reality is that it will only flag for three-character strings where...
 >> s[0] != 'c'
 >> s[1] == 'e'
 >> s[2] == 'i'
 >> s[>2] can be anything, we would need to use "$" to signify a terminating character
 >> in fact, there can be any amount of characters before or after our "[^c]ei" string
 
 >> If we use "[^c]ei[^r]", then our std::regex_search will ring true where:
 >> s[0] != 'c' || s[3] != 'r'
 >> s[1] == 'e'
 >> s[2] == 'i'
 
*/

#include <regex>
#include <string>
#include <iostream>

int main()
{
    std::cout << "Welcome to the \"i\" before \"e\", noexcept after C++ tester!\n\n";
    std::cout << "Please enter a word you would like to test, or enter \"q\" to quit: ";
    
    // std::regex r("[^c]ei$");
    std::regex r("[^c]ei[^r]");
    
    std::string s;
    std::smatch results;
    
    while (std::cin >> s && s != "q") {
        
        if (std::regex_search(s, results, r))
            std::cout << "\"" << s << "\" fails the test! ";
        else
            std::cout << "\"" << s << "\" passes the test! ";
        
        std::cout << "Try another word: ";
    }
    
    return 0;
}
