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

using primerLib::compute;

void compute(int) { std::cout << "primerLib::compute::compute(int)" << std::endl; }
void compute(double, double = 3.4) { std::cout << "primerLib::compute::compute(double, double = 3.4)" << std::endl; }
void compute(char*, char* = 0) { std::cout << "primerLib::compute::compute(char*, char* = 0)" << std::endl; }

void f() { compute("manbearpig"); }

int main()
{
    f();
    
    // void f() { compute(0); }
    // should call (int) overload...which it does
    // primerLib::compute::compute(int)
    
    // void f() { compute(); }
    // primerLib::compute()
    
    // void f() { compute('c', 0); }
    // primerLib::compute::compute(double, double = 3.4)
    
    // void f() { compute("woof", 0); }
    // primerLib::compute::compute(char*, char* = 0)
    
    // void f() { compute("manbearpig"); }
    // primerLib::compute(const void*)
    
    return 0;
}
