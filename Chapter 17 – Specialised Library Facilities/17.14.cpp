// Exercise 17.14:
/*
 Write several regular expressions designed to trigger various errors.
 Run your program to see what output your compiler generates for each error.
 
 >> Various errors recorded below main(), along with what amendments caused them
*/

#include <regex>
#include <string>
#include <iostream>

int main()
{
    try {
        std::regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
        std::cmatch results;
        if (std::regex_search("main.cpp", results, r))
            std::cout << results.str() << std::endl;
    } catch (std::regex_error e) {
        std::cout << e.what() << "\ncode: " << e.code() << std::endl;
    }
    
    return 0;
}

// std::regex r("[[(:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
// The parser did not consume the entire regular expression.
// code: 17

// std::regex r("[[:alnum:}]]+\\.(cpp|cxx|cc)$", std::regex::icase);
// The expression contained mismatched [ and ].
// code: 5

// std::regex r("[[:alnum:]]+\\.((cpp|cxx|cc)$", std::regex::icase);
// The expression contained mismatched ( and ).
// code: 6

// if (std::regex_search("main3.cpp", results, r))
// does throw an error

// std::regex r("*[[:alnum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
// One of *?+{ was not preceded by a valid regular expression.
// code: 11
