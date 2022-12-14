// Exercise 16.50:
/*
 Define the functions from the previous exercise so that they print an identifying message.
 Run the code from that exercise.
 If the calls behave differently from what you expected, make sure you understand why.
*/

#include <iostream>

template <typename T> void f(T) { std::cout << "f(T)" << std::endl; }
template <typename T> void f(const T*) { std::cout << "f(const T*)" << std::endl; }
template <typename T> void g(T) { std::cout << "g(T)" << std::endl; }
template <typename T> void g(T*) { std::cout << "g(T*)" << std::endl; }

int main()
{
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;
    
    std::cout << "(a) "; g(42);      // g(T) is called; "42" is an int literal
    std::cout << "(b) "; g(p);       // g(T*) is called; "p" is an int*
    std::cout << "(c) "; g(ci);      // g(T) is called; "ci" is a const lvalue, but not a pointer
    std::cout << "(d) "; g(p2);      // g(T*) is called; "p2" is an int*
    std::cout << "(e) "; f(42);      // f(T) is called; "42" is an int literal
    std::cout << "(f) "; f(p);       // f(T) is called; "p" is not a const int*
    std::cout << "(g) "; f(ci);      // f(T) is called; "ci" is not a const int*
    std::cout << "(h) "; f(p2);      // f(const T*) is called; "p2" IS a const int*
    
    return 0;
}
