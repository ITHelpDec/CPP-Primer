// Exercise 17.21:
/*
 Rewrite your phone number program from § 8.3.2 (p. 323) to use the valid function defined in this section.
*/

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

// taken from pg. 741
bool valid(const std::smatch &results) {
    return results[1].matched
        ? results[3].matched && (results[4].matched == 0 || results[4].str() == " ")
        : !results[3].matched && results[4].str() == results[6].str();
}

int main()
{
    std::ifstream file("phones");
    
    if (!file.is_open()) {
        std::cerr << "Unable to open file.\n" << std::endl; return -1;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    std::string line, word;
    std::vector<PersonInfo> people;
    
    while (std::getline(file, line)) {
        PersonInfo info;
        std::istringstream record(line);
        record >> info.name;
        while (record >> word)
            info.phones.push_back(word);
        people.push_back(info);
    }
    
    std::regex r("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})");
    
    for (const auto &entry : people) {
        std::ostringstream formatted, bad_nums;
        for (const auto &nums : entry.phones) {
            // sregex_iterator loop added, with amendments to bad_nums and formatted
            for (std::sregex_iterator it(nums.begin(), nums.end(), r), end_it; it != end_it; ++it) {
                !valid(*it)
                    ? bad_nums << it->str() << " " << nums
                    : formatted << "(" << it->str(2) << ")-" << it->str(5) << "-" << it->str(7);
            }
        }
        
        // no real changes needed here
        bad_nums.str().empty()
            ? std::cout << entry.name << " " << formatted.str() << std::endl
            : std::cerr << "input error: " << entry.name
                        << "\ninvalid number(s) " << bad_nums.str() << "\n" << std::endl;
    }
    
    file.close();
    
    if (file.is_open()) {
        std::cerr << "Unable to close file.\n" << std::endl; return -1;
    } std::cout << "File closed successfully.\n" << std::endl;
    
    return 0;
}
