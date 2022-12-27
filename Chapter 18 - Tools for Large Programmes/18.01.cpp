// Exercise 18.01:
/*
 What is the type of the exception object in the following throws?
 
 // (a)
 // range_error r("error");
 // throw r;
 
 // (b)
 // exception *p = &r;
 // throw *p;
 
 "When we throw an expression, the static, compile-time type (§ 15.2.3, p. 601) of that expression determines the type of the exception object." – pg. 774
*/

#include <iostream>
#include <stdexcept>

void a(int i) {
    std::range_error r("error");
    
    std::cout << "(a) Enter a number no greater than 10:\n>>> ";
    while (std::cin >> i) {
        if (i > 10)
            throw r;
        std::cout << ">>> ";
    }
    
    // libc++abi: terminating with uncaught exception of type std::range_error: error
    // terminating with uncaught exception of type std::range_error: error
}

void b(int i) {
    std::range_error r("error");
    
    std::exception *p = &r;
    
    std::cout << "(b) Enter a number no greater than 10:\n>>> ";
    while (std::cin >> i) {
        if (i > 10)
            throw *p;
        std::cout << ">>> ";
    }
    
    // libc++abi: terminating with uncaught exception of type std::exception: std::exception
    // terminating with uncaught exception of type std::exception: std::exception
}

void c(int i) {
    std::range_error r("error");
    
    std::exception *p = &r;
    
    std::cout << "(c) Enter a number no greater than 10:\n>>> ";
    while (std::cin >> i) {
        if (i > 10)
            throw p;
        std::cout << ">>> ";
    }
    
    // libc++abi: terminating with uncaught exception of type std::exception*
    // terminating with uncaught exception of type std::exception*
}

int main()
{
    int i = 0;
    
    // a(i);
    // b(i);
    // c(i);
    
    return 0;
}
