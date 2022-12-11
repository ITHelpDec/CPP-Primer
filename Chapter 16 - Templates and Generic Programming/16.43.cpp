// Exercise 16.43:
/*
 Using the function defined in the previous exercise, what would the template parameter of g be if we called g(i = ci)?
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
    
    // (d)
    // argument is an lvalue REFERRING to the object integer "i"
    // template parameter T is deduced as int &val -> int& &&
    // val = int& && = int&
    // any change
    std::cout << "(d): "; g(i = ci);
    
    return 0;
}
