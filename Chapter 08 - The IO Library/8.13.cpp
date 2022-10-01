// Exercise 8.11:
/*
 TRewrite the phone number program from this section to read from a named file rather than from cin.
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "No file included in arguments." << std::endl;
        return -1;
    }
    
    if (argc > 2) {
        std::cerr << "Too many arguments provided." << std::endl;
        return -1;
    }
    std::ifstream in(argv[1]);
    
    if (!in) {
        std::cerr << "File not found." << std::endl;
        return -1;
    }
    
    std::cout << "File opened successfully." << std::endl;
    
    std::string line, word;
    std::vector<PersonInfo> people;
    
    std::cout << "The phone numbers in the file provided are as follows: " << std::endl;
    
    // while (std::getline(std::cin, line)) {
    // replace std::cin with in
    while (std::getline(in, line)) {
        PersonInfo info;
        std::istringstream record(line);
        record >> info.name;
        while (record >> word) {
            std::cout << word << " ";
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    
    return 0;
}
