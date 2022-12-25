// Exercise 17.22:
/*
 Rewrite your phone program so that it allows any number of whitespace characters to separate the three parts of a phone number.
 
 >> Phone programme is overly-architected, and was producing strange results – no need for the "valid" function when we can format it ourselves
*/

#include<fstream>
#include <regex>
#include <iostream>

int main()
{
    std::ifstream file("phones");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n" << std::endl;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    // \d – digits
    // \D – non-digits
    std::regex r("\\D?(\\d{3})\\D*(\\d{3})\\D*(\\d{4})");
    
    std::string line;
    
    while (std::getline(file, line)) {
        for (std::sregex_iterator it(line.begin(), line.end(), r), end_it; it != end_it; ++it)
            std::cout << "(" << it->str(1) << ")-" << it->str(2) << "-" << it->str(3) << std::endl;
    }
    
    // output:
    // (201)-555-0168
    // (862)-555-0123
    // (973)-555-0130
    // (609)-555-0132
    // (201)-555-0175
    // (800)-555-0110
    
    file.close();
    
    if (file.is_open()) {
        std::cerr << "\nUnable to close file." << std::endl;
    } std::cout << "\nFile close successfully." << std::endl;
    
    return 0;
}

