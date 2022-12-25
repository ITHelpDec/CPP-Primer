// Exercise 17.27:
/*
 Write a program that reformats a nine-digit zip code as ddddd-dddd.
 
 >> Didn't know there was such a thing
 >> Would have been handy if they gave test cases
*/

#include <string>
#include <iostream>
#include <regex>

int main()
{
    std::string test_str = "908.647.4306 164 gates, 07933 07933-1257";
    
    std::regex r("\\d{5}-\\d{4}", std::regex::icase);
    
    std::smatch results;
    if (std::regex_search(test_str, results, r))
        std::cout << results.str() << std::endl;
    
    return 0;
}
