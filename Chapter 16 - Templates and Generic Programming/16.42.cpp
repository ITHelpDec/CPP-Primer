// Exercise 16.42:
/*
 Determine the type of T and of val in each of the following calls:
*/

#include <iostream>

template <typename T> void g(T&& val) {
    std::cout << val << std::endl;
}

int main()
{
    int i = 2;
    const int ci = 3;
    
    // (a)
    // argument is an lvalue; template parameter T is deduced as int&
    // val == int& && == int&
    std::cout << "(a): "; g(i);
    
    // (b)
    // argument is an lvalue; template parameter T is deduced as const int&
    // val == const int& && == const int&
    std::cout << "(b): "; g(ci);
    
    // (c)
    // argument is an rvalue; template parameter T is deduced as int
    // val == int&& && == int&&
    std::cout << "(c): "; g(i * ci);
    
    return 0;
}
