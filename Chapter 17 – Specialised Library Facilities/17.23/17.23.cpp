// Exercise 17.23:
/*
 Write a regular expression to find zip codes. A zip code can have five or nine digits.
 The first five digits can be separated from the remaining four by a dash.
 
 // Did UK postcodes instead.
*/

#include <fstream>
#include <iostream>
#include <regex>
#include <string>

void extractPostCodes(std::ifstream &file) {
    std::regex r("([[:alpha:]]{1,2})([[:digit:]]{1,2}) ([[:digit:]]{1})([[:alpha:]]{2})");
    // 1: ([[:alpha:]]{1,2}) – one or two letters
    // 2: ([[:num:]]{1,2})   – one or two numbers
    // 3: ([[:digit:]]{1})   – one number
    // 4: ([[:alpha:]]{2})   – last two letters
    
    std::string line;
    while (std::getline(file, line)) {
        for (std::sregex_iterator it(line.begin(), line.end(), r), end_it; it != end_it; ++it) {
            std::cout << it->str(1) << it->str(2) << " " << it->str(3) << it->str(4) << std::endl;
        }
    }
}

int main()
{
    std::ifstream file("postcodes");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n" << std::endl; return -1;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    extractPostCodes(file);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    file.close();
    
    if (file.is_open()) {
        std::cerr << "\nUnable to close file.\n" << std::endl; return -1;
    } std::cout << "\nFile closed successfully.\n" << std::endl;
    
    return 0;
}
