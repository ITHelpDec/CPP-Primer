// Exercise 18.20:
/*
 In the following code, determine which function, if any, matches the call to compute.
 List the candidate and viable functions.
 What type conversions, if any, are applied to the argument to match the parameter in each viable function?
 */

#include <iostream>

namespace primerLib {
void compute() { std::cout << "primerLib::compute()" << std::endl; }
void compute(const void *) { std::cout << "primerLib::compute(const void*)" << std::endl; }
}

// using primerLib::compute;

void compute(int) { std::cout << "compute(int)" << std::endl; }
void compute(double, double = 3.4) { std::cout << "compute(double, double = 3.4)" << std::endl; }
void compute(char*, char* = 0) { std::cout << "compute(char*, char* = 0)" << std::endl; }

void f() { compute("manbearpig"); }

// What would happen if the using declaration were located in main before the call to compute?
// Answer the same questions as before.
using primerLib::compute;

int main()
{
    f();
    
    // void f() { compute(0); }
    // should still call (int) overload...which, again, it does
    // compute(int)

    // void f() { compute(); }
    // error: "No matching function for call to 'compute'"
    // would need to explicitly call namespace
    // void f() { primerLib::compute(); }
    // primerLib::compute()
    
    // void f() { compute('c', 0); }
    // compute(double, double = 3.4)

    // void f() { compute("woof", 0); }
    // compute(char*, char* = 0)

    // void f() { compute("manbearpig"); }
    // compute(char*, char* = 0)
    // no longer primerLib::compute(const void*)
    
    return 0;
}
