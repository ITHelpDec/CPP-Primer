// Exercise 17.20:
/*
 Write your own version of the program to validate phone numbers.
 
 // I've ignored the valid function from pg. 740.
 // It shows numbers with poor formatting, but we can correct that using the code below.
 
 // there was also a type in the std::regex from pg. 740
 // "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
 // instead of
 // "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
 // expression 6's "?" is in the wrong place
 
*/

#include <fstream>
#include <iostream>
#include <regex>

int main()
{
    std::ifstream file("phones");
    
    if (!file.is_open()) {
        std::cerr << "File not found.\n" << std::endl; return -1;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    // 1: (\\()?    – optional opening parenthesis "("
    // 2: (\\d{3})  – 3 numbers
    // 3: (\\))?    – optional closing parenthesis ")"
    // 4: ([-. ])?  – optional separator "-", "." or " "
    // 5: (\\d{3})  – 3 more numbers
    // 6: ([-. ])?  – another operational separator
    // 7: (\\d{4})  – final 4 numbers
    //
    // we want 2, 5 and 7
    
    std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    std::smatch results;
    std::string line;
    
    while (std::getline(file, line))
        for (std::sregex_iterator it(line.begin(), line.end(), r), end_it; it != end_it; ++it)
                std::cout << "Valid phone number: (" << it->str(2) << ")-" << it->str(5) << "-" << it->str(7) << std::endl;
    
    file.close();
    
    if (file.is_open()) {
        std::cerr << "\nUnable to close file." << std::endl; return -1;
    } std::cout << "\nFile closed successfully.\n" << std::endl;
    
    return 0;
}
