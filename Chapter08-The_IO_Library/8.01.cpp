// Exercise 8.1:
/*
 Write a function that takes and returns an istream&.
 The function should read the stream until it hits end-of-file.
 The function should print what it reads to the standard output.
 Reset the stream so that it is valid before returning the stream.
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
