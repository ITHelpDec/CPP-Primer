// Exercise 8.11:
/*
 The program in this section defined its istringstream object inside the outer while loop.
 What changes would you need to make if record were defined outside that loop?
 Rewrite the program, moving the definition of record outside the while, and see whether you thought of all the changes that are needed.
 
 morgan 2015552368 8625550123
 drew 9735550130
 lee 6095550132 2015550175 8005550000
 
*/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

int main()
{
    std::string line, word;
    std::vector<PersonInfo> people;
    
    // std::istringstream record(line);
    // record defined outside the loop
    std::istringstream record;
    
    while (std::getline(std::cin, line)) {
        // clear stream at beginning of loop
        // will produce funny results if stream isn't cleared
        record.clear();
        PersonInfo info;
        // std::istringstream record(line);
        // use str() to bind contents of line to record
        record.str(line);
        record >> info.name;
        while (record >> word) {
            std::cout << word << " ";
            info.phones.push_back(word);
        }
        people.push_back(info);
    }
    
    return 0;
}
