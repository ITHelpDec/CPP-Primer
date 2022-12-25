// Exercise 17.26:
/*
 Rewrite your phone program so that it writes only the second and subsequent phone numbers for people with more than one phone number.
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
    
    std::ofstream output("numbers_after_first");
    
    for (const auto &person : people) {
        output << person.name << " ";
        if (person.phones.size() > 1) {
            for (int i = 1; i != person.phones.size(); ++i)
                output << person.phones[i] << " ";
        } output << std::endl;
    }
    
    output.close();
    file.close();
    
    if (file.is_open()) {
        std::cerr << "Unable to close input file." << std::endl; return -1;
    } std::cout << "Input file closed successfully." << std::endl;
    
    return 0;
}
