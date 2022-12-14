// Exercise 17.25:
/*
 Rewrite your phone program so that it writes only the first phone number for each person.
*/

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

int main()
{
    std::ifstream file("phones");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open input file." << std::endl; return -1;
    } std::cout << "Input file opened successfully." << std::endl;
    
    std::vector<PersonInfo> people;
    
    std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    
    std::string line;
    while (std::getline(file, line)) {
        PersonInfo person;
        std::istringstream record(line);
        record >> person.name;
        
        std::string numbers, substr;
        while (record >> substr) { numbers += substr + " "; }
        
        std::string fmt = "$2.$5.$7";
        for (std::sregex_iterator it(numbers.begin(), numbers.end(), r), end_it; it != end_it; ++it)
            person.phones.push_back(std::regex_replace(it->str(), r, fmt));
        
        people.push_back(person);
    }
    
    std::ofstream output("first_numbers_only");
    
    for (const auto &person : people) {
        output << person.name << " ";
        if (!person.phones.empty())
            output << person.phones[0] << std::endl;
    }
    
    output.close();
    file.close();
    
    if (file.is_open()) {
        std::cerr << "Unable to close input file." << std::endl; return -1;
    } std::cout << "Input file closed successfully." << std::endl;
    
    return 0;
}
