// Exercise 9.45:
/*
Write a funtion that takes a string representing a name and two other strings representing a prefix, such as “Mr.” or “Ms.” and a suffix, such as “Jr.” or “III”.
 Using iterators and the insert and append functions, generate and return a new string with the suffix and prefix added to the given name.
 
 >> Which would be better – keeping the scope within the function, or referencing the name for a more permanent change?
 >> Below I've kept the changes local to preserve the original names, but the name string could also be modified permanently if needs be
*/

#include <string>
#include <iostream>

void presuf(std::string name, const std::string prefix, const std::string suffix)
{
    std::cout << "Input: " << name << std::endl;
    
    name.insert(0, prefix + " ");
    name.append(" " + suffix);
    
    std::cout << "Output: " << name << std::endl;
}

int main()
{
    presuf("Elizabeth", "Queen", "II");
    
    presuf("Charles", "King", "III");
    
    return 0;
}
