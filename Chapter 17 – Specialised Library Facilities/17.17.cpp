// Exercise 17.17:
/*
 Update your program so that it finds all the words in an input sequence that violiate the “ei” grammar rule.
 
 >> Updated programme to work file std::vector<std::string> instead of std::string
*/

#include <regex>
#include <vector>
#include <string>
#include <iostream>

void culpritsInContext(const std::regex &r, std::vector<std::string> &file) {
    for (const std::string &s : file) {
        for (std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it) {
            auto pos = it->prefix().length();
            pos = pos > 15 ? pos - 15 : 0;
            
            std::cout << "..." << it->prefix().str().substr(pos)
                      << " >>> " << it->str() << " <<< "
                      << it->suffix().str().substr(0, 15) << "..."
                      << std::endl;
        }
    } std::cout << std::endl;
}

int main()
{
    std::regex r("[[:alpha:]]*[^c]ei[^r][[:alpha:]]*");
    
    std::vector<std::string> file = {
        "Hi there! Could I get a refund for this textbook? Here's my receipt.",
        "Why did I buy it? A friend of mine recommended I pick it up.",
        "Why did I buy it? A freind of mine recommended I pick it up.",
        "You'd think I were a common theif – I'm gaining so much knowledge for so little money.",
        "You'd think I were a common thief – I'm gaining so much knowledge for so little money.",
        "Yes, I could have borrowed their copy, but I prefer having my own." };
    
    culpritsInContext(r, file);
    
    return 0;
}
