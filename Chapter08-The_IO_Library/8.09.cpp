// Exercise 8.09:
/*
 Use the function you wrote for the first exercise in § 8.1.2 (p. 314) to print the contents of an istringstream object.
*/

#include <iostream>
#include <string>
#include <sstream>

std::istream &read(std::istream &is)
{
    // crete string to store input
    std::string s;
    
    // read the strings from the input stream until end-of-file
    while (is >> s)
        std::cout << s << " ";  // print strings
    
    std::cout << std::endl;
    
    // Reset stream so that it is valid before returning stream
    std::cin.clear();
    
    // return stream
    return is;
}



int main()
{
    std::string s;                  // create local string
    std::getline(std::cin, s);      // read a line from user and store it to "s"
    std::istringstream iss(s);      // bind contents of "s" to an istringstream
    read(iss);                      // get read() function to read contents of istringstream
    
    return 0;
}
