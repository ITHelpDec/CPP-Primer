// Exercise 9.47:
/*
 Write a program that finds each numeric character and then each alphabetic character in the string "ab2c3d7R4E6".
 Write two versions of the program. The first should use find_first_of, and the second find_first_not_of.
 
 >> Feels a bit messy having a string dedicated to all the letters of the alphabet
 >> Would be nice if you could do find_first_of(!numbers, pos) to find the letters
 >> find_first_not_of(numbers, pos) works just as well
*/

#include <string>
#include <iostream>

void of(const std::string &s, const std::string &numbers, const std::string &letters)
{
    std::cout << "Performing find_first_of:" << std::endl << std::endl;
    // initialise size_type to keep track of iterations through string
    std::string::size_type pos = 0;
    
    // function will only equal npos if no match is found
    // i.e. for as long as matches are found, do something
    std::cout << "Finding numbers..." << std::endl;
    while ( (pos = s.find_first_of(numbers, pos)) != std::string::npos) {
        std::cout << s[pos] << " is character number " << pos << std::endl;
        ++pos;
    }
    
    std::cout << std::endl;

    // reset counter to find letters
    pos = 0;
    std::cout << "Finding letters..." << std::endl;
    while ( (pos = s.find_first_of(letters, pos)) != std::string::npos) {
        std::cout << s[pos] << " is character number " << pos << std::endl;
        ++pos;
    }
}

void notof(const std::string &s, const std::string &numbers, const std::string &letters)
{
    std::cout << "Performing find_first_not_of:" << std::endl << std::endl;
    std::string::size_type pos = 0;
    
    std::cout << "Finding numbers..." << std::endl;
    while ( (pos = s.find_first_not_of(letters, pos)) != std::string::npos) {
        std::cout << s[pos] << " is character number " << pos << std::endl;
        ++pos;
    }
    
    std::cout << std::endl;

    pos = 0;
    std::cout << "Finding letters..." << std::endl;
    while ( (pos = s.find_first_not_of(numbers, pos)) != std::string::npos) {
        std::cout << s[pos] << " is character number " << pos << std::endl;
        ++pos;
    }
}

int main()
{
    std::string s = "ab2c3d7R4E6";
    std::string numbers = "0123456789";
    std::string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    of(s, numbers, letters);
    
    std::cout << std::endl;
    
    notof(s, numbers, letters);
    
    return 0;
}
