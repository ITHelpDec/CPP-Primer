// Exercise 14.36:
/*
 Use the class from the previous exercise to read the standard input, storing each line as an element in a vector.
*/

#include <iostream>
#include <string>
#include <vector>

class PrintString {
    
public:
    PrintString(std::ostream &o = std::cout) : os(o) { }
    
    void operator() (const std::string &s) const { return os << s; }
    
private:
    std::ostream &os;
};

int main()
{
    std::cout << "Please write a few lines of text:\n";
    std::string s;
    std::vector<std::string> svec;
    
    // really like this line
    // read line – if std::cin fails, push "" instead of "s"
    while (std::getline(std::cin, s)) { svec.push_back((std::cin) ? s : ""); }
    
    PrintString ps;
    
    // use ps object to print each string in vector
    for (const auto &e : svec) {
        std::cout << "\""; ps(e); std::cout << "\" ";
    } std::cout << std::endl;
    
    return 0;
}
