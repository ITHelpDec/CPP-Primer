// Exercise 18.17:
/*
 Write code to test your answers to the previous question.
 */

#include <iostream>

namespace Exercise {
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}

int ivar = 0;

// position 1
// "...replace the using declarations with a using directive..."
using namespace Exercise;

void manip()
{
    // position 2
    double dvar = 3.1416;
    std::cout << dvar << "\n";
    
    int iobj = limit + 1;
    std::cout << iobj << "\n";
    
    // ++ivar;
    // std::cout << ivar << "\n";
    // error:
    // "Reference to 'ivar' is ambiguous"
    // Explicitly declare namespace, or remove
    ++Exercise::ivar;
    std::cout << Exercise::ivar << "\n";
    
    ++::ivar;
    std::cout << ::ivar << std::endl;
}

int main()
{
    manip();
    
    return 0;
}

// output
// 3.1416
// 1001
// 1
// 1
