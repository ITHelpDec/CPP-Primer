// Exercise 17.24:
/*
 Write your own version of the program to reformat phone numbers.
*/

#include <fstream>
#include <iostream>
#include <regex>

int main()
{
    std::ifstream file("phones");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open input file." << std::endl; return -1;
    } std::cout << "Input file opened successfully." << std::endl;
    
    std::ofstream output("phones_formatted");
    
    if (!output.is_open()) {
        std::cerr << "Unable to open output file.\n" << std::endl; return -1;
    } std::cout << "Output file opened successfully.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    std::string format = "$2.$5.$7";
    
    std::string line;
    while (std::getline(file, line))
        output << std::regex_replace(line, r, format) << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    output.close();
    file.close();
    
    return 0;
}
