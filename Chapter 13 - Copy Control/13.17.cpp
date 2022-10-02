// Exercise 13.17:
/*
 Write versions of numbered and f corresponding to the previous three exercises and check whether you correctly predicted the output.
 
 >> I have changed all of the "unsigned" types to "size_t"
 
 // size_t has a specific restriction.
 //
 // Quoting from http://www.cplusplus.com/reference/cstring/size_t/ :
 //
 // Alias of one of the fundamental unsigned integer types.
 //
 // It is a type able to represent the size of any object in bytes:
 // size_t is the type returned by the sizeof operator and is widely used in the standard library to represent sizes and counts.
 
 */

#include <iostream>

class Numbered {
public:
    Numbered() : mysn(++sn_counter) { std::cout << "N()" << std::endl; }
    
    Numbered(const Numbered&) : mysn(++sn_counter) { std::cout << "N() copy" << std::endl; }
    
    // explicit copy-assign operator declaration
    Numbered& operator=(const Numbered&) { std::cout << "N() copy assign" << std::endl; return *this; }
    
    // no need for an explicit destructor, but declared anyway for clarity
    ~Numbered() { std::cout << "~N()" << std::endl; }
    
    static std::size_t sn_counter;
    std::size_t mysn;
};

std::size_t Numbered::sn_counter = 0;

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
