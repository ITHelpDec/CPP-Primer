// Exercise 17.18:
/*
 Revise your program to ignore words that contain “ei” but are not misspellings, such as “albeit” and “neighbor.”
 
 >> Pull requests with testcases are welcome
 
*/

#include <regex>
#include <vector>
#include <string>
#include <iostream>

void culpritsInContext(const std::regex &r1, std::vector<std::string> &file) {
    for (const std::string &s : file) {
        for (std::sregex_iterator it(s.begin(), s.end(), r1), end_it; it != end_it; ++it) {
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
    // pattern1: "[^c]ei[^(r|g|t)]" // i-befor-e rule
    // pattern2: "ie[^(f|n|r)]"     // catch mispellings
    // ( | ) "or" logic used to combine the rules, although I'm sure there's a prettier way to do this
    std::regex r("[[:alpha:]]*([^c]ei[^(r|g|t)]|ie[^(f|n|r)])[[:alpha:]]*");
    
    std::vector<std::string> file = {
        "Hi there! Could I get a refund for this textbook? Here's my receipt.",
        "Why did I buy it? A freind of mine's nieghbour recommended I pick it up.",
        "You'd think I were a common theif – my friend I'm gaining so much knowledge for so little money.",
        "You'd think I were a common thief – I'm gaining so much knowledge for so little money.",
        "Yes, albiet, I could have borrowed my niehgbour's copy (slieght of hand), but I prefer having my own."
    };
    
    culpritsInContext(r, file);
    
    return 0;
}
