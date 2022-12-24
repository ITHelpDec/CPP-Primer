// Exercise 17.15:
/*
 Write a program using the pattern that finds words that violate the “i before e except after c” rule.
 Have your program prompt the user to supply a word and indicate whether the word is okay or not.
 Test your program with words that do and do not violate the rule.
 
 // tweaked first pattern to detect "their"
 // created second pattern to detect "receipt" vs "reciept"
 
 // original "[^c]ei" regex did not detect these violations
*/

#include <regex>
#include <string>
#include <iostream>

int main()
{
    std::cout << "Welcome to the \"i\" before \"e\", noexcept after C++ tester!\n\n";
    std::cout << "Please enter a word you would like to test, or enter \"q\" to quit: ";
    
    std::string pattern1 = "[^c]ei[^r]";
    std::string pattern2 = "cie";
    
    std::regex r1("[[:alpha:]]*" + pattern1 + "[[:alpha:]]*");
    std::regex r2("[[:alpha:]]*" + pattern2 + "[[:alpha:]]*");
    
    std::string s;
    std::smatch results;
    
    while (std::cin >> s && s != "q") {
        
        if (std::regex_search(s, results, r1) || std::regex_search(s, results, r2))
            std::cout << "\"" << s << "\" fails the test! ";
        else
            std::cout << "\"" << s << "\" passes the test! ";
        
        std::cout << "\nTry another word: ";
    }
    
    return 0;
}
