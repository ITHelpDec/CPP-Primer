// Exercise 13.16:
/*
 What if the parameter in f were const numbered&?
 Does that change the output?
 If so, why?
 What output gets generated?
*/

#include <iostream>

class Numbered {
public:
    Numbered() : mysn(++sn_counter) { std::cout << "N()" << std::endl; }
    
    Numbered(const Numbered&) : mysn(++sn_counter) { std::cout << "N() copy" << std::endl; }
    
    // synthesised copy-assignment operator
    
    // synthesised destructor
    
    static unsigned sn_counter;
    unsigned mysn;
};

unsigned Numbered::sn_counter = 0;

// void f(Numbered s)
// calling a const reference will use the synthesised copy-assignment operator instead of copy
void f(const Numbered &s)
{
    std::cout << "Serial number: " << s.mysn << std::endl;
}

int main()
{
    // one constructor, two copies
    Numbered a, b = a, c = a;

    // output:
    f(a);   // 1
    f(b);   // 2
    f(c);   // 3
    
    return 0;
}