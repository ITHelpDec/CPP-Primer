// Exercise 9.46:
/*
 Rewrite the previous exercise using a position and length to manage the strings.
 This time use only the insert function.
*/

#include <string>
#include <iostream>

void presuf(std::string name, const std::string prefix, const std::string suffix)
{
    std::cout << "Input: " << name << std::endl;
    
    name.insert(0, prefix + " ");
    // name.append(" " + suffix);
    name.insert(name.size()," " + suffix);
    
    std::cout << "Output: " << name << std::endl;
}

int main()
{
    presuf("Elizabeth", "Queen", "II");
    
    presuf("Charles", "King", "III");
    
    return 0;
}
