// Exercise 14.35:
/*
 Write a class like PrintString that reads a line of input from an istream and returns a string representing what was read.
 If the read fails, return the empty string.
*/

#include <iostream>
#include <string>

// class is called PrintString, not PrintIstream,
// so will capture istream outside of class to stay true to class purpose
class PrintString {
public:
    // default constructor
    PrintString(std::ostream &o = std::cout) : os(o) { }
    
    // output operator()
    void operator() (const std::string &s) const { return os << s; }
private:
    std::ostream &os;
};

int main()
{
    // take input from user (std::cin is an object of class istream)
    std::cout << "Please intput a word: ";
    std::string s;
    
    // "If the read fails, return the empty string"
    if (!(std::cin >> s)) { s = ""; }
    
    // create object then pass string as argument
    PrintString ps;
    std::cout << "ps(s) = \""; ps(s);
    std::cout << "\"" << std::endl;
    
    return 0;
}
