// Exercise 19.26:
/*
 Explain these declarations and indicate whether they are legal:
*/

extern "C" int compute(int*, int);

// extern "C" is a linking directive that allows the compiler...
// ... to call functions written in other languages (in this case, "C")

// the function above declares a "compute" function with two parameters:
// a pointer to an integer, and an integer
// this is a single-statement linkage directive

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// extern "C" double compute(double *, double);  - -- -- -- -- -- -- -- -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// the above code basically is the same, only this time with doubles instead of ints
// however, "the C language does not support function overloading", so we must be careful...
// ... to not declare these functions within the same scope (* pg. 860)

// error:
// "Functions that differ only in their return type cannot be overloaded"

#include "compute.c"

#include <iostream>

int main()
{
    int j = 4;
    int *p = &j;
    
    std::cout << compute(p, j) << std::endl;
    
    return 0;
}
