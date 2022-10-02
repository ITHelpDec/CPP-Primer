// Exercise 13.15:
/*
 Assume numbered has a copy constructor that generates a new serial number.
 Does that change the output of the calls in the previous exercise?
 If so, why? What output gets generated?
*/

#include <iostream>

class Numbered {
public:
    Numbered() : mysn(++sn_counter) { std::cout << "N()" << std::endl; }
    
    // copy constructor (non-synthesised)
    Numbered(const Numbered&) : mysn(++sn_counter) { std::cout << "N() copy" << std::endl; }
    
    // synthesised copy-assign
    
    // synthesised destructor
    
    static unsigned sn_counter;
    unsigned mysn;
};

// cannot declare a static member inside the class body
// must be declared outside
unsigned Numbered::sn_counter = 0;

void f(Numbered s)
{
    std::cout << "Serial number: " << s.mysn << std::endl;
}

int main()
{
    // one constructor, two copies
    Numbered a, b = a, c = b;
    
    // below, each function creates a copy of the parameter because it is a nonreference call, therefore...

    // output:
    f(a);   // 4
    f(b);   // 5
    f(c);   // 6
    
    return 0;
}
