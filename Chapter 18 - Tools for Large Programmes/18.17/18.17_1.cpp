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
// "...assuming using declarations are at position 1..."
using /* Exercise::ivar, */ Exercise::dvar, Exercise::limit;

// error:
// "Target of using declaration conflicts with declaration already in scope"
// need to remove using declaration for Exercicse::ivar

void manip()
{
    // position 2
    double dvar = 3.1416;
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
// 2
