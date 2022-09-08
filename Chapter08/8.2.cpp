// Exercise 8.2:
/*
 Test your function by calling it, passing cin as an argument.
 
 (same as exercise 8.1)
*/

#include <iostream>
#include <string>

std::istream &read(std::istream &is)
{
    // crete string to store input
    std::string s;
    
    // provdded input is valid, loop will run until end-of-file
    while (std::cin >> s)
        std::cout << s << std::endl;    // print what's read to standard output
    
    // Reset stream so that it is valid before returning stream
    std::cin.clear();
    
    // return stream
    return is;
}



int main()
{
    read(std::cin);
    
    return 0;
}
