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

void manip()
{
    // position 2
    // "...what if they appear at position 2 instead..."
    using Exercise::ivar, /*Exercise::dvar,*/ Exercise::limit;
    
    double dvar = 3.1416;
    // error:
    // "Declaration conflicts with target of using declaration already in scope"
    // remove Exercise::dvar
    std::cout << dvar << "\n";
    
    int iobj = limit + 1;
    std::cout << iobj << "\n";
    
    ++ivar;
    std::cout << ivar << "\n";
    
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
