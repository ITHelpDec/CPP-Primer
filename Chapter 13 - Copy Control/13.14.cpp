// Exercise 13.14:
/*
 Assume that numbered is a class with a default constructor that generates a unique serial number for each object, which is stored in a data member named "mysn".
 Assuming numbered uses the synthesized copy-control members and given the following function:
*/

// void f (Numbered s) { std::cout << s.mysn << std::endl; }

/*
 ...what output does the following code produce?
*/

#include <iostream>

class Numbered {
public:
    // default constructor (taken from source code)
    // "mysn" is set to the next serial number every time the constructor is called
    Numbered() : mysn(++sn_counter) { }
    
    // sythesised copy
    
    // synthesised copy-assign
    
    // synthesised destructor
    
    // static member to hold count (only nonstatic members copied)
    static unsigned sn_counter;
    // nonstatic unsigned to store unique seriable number
    unsigned mysn;
};

// cannot declare a static member inside the class body
// must be declared outside
unsigned Numbered::sn_counter = 0;

void f(Numbered s)
{
    // mysn left as public member in the struct
    // would need separate function within the struct body to call "mysn" if it were a private variable
    std::cout << "Serial number: " << s.mysn << std::endl;
}

int main()
{
    // one constructor; two copy-assignment operators
    Numbered a, b = a, c = b;
    
    // using a sythesised copy-assignment constructor, all f(arg) calls will show the serial number as "1" instead of incrementing
    f(a);
    f(b);
    f(c);
    
    return 0;
}
