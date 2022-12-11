# CPP-Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (11/12/2022) .:.

```cpp
// Exercise 16.44:
/*
 Using the same three calls as in the first exercise, determine the types for T if g’s function parameter is declared as T (not T&&).
 What if g’s function parameter is const T&?
*/

#include <iostream>

template <typename T> void g1(T val) {
    std::cout << val << std::endl;
}

// like in page 687
template <typename T> void g2(const T &val) {
    std::cout << val << std::endl;
}

int main()
{
    int i = 2;
    const int ci = 3;
    
    // (a)
    // argument is an lvalue; template parameter T is deduced as int
    // "val" is a copy of "i" (int)
    std::cout << "(a): "; g1(i);
    
    // (b)
    // argument is an lvalue; template parameter T is deduced as int (const is ignored)
    // val is an int copy of "ci"
    std::cout << "(b): "; g1(ci);
    
    // (c)
    // argument is an rvalue; template parameter T is deduced as int
    // val is a new int of the product of i and ci
    std::cout << "(c): "; g1(i * ci);
    
    // (d)
    // argument is an lvalue; template parameter T is deduced as int
    // val == const int&
    std::cout << "(d): "; g2(i);
    
    // (e)
    // argument is an lvalue; template parameter T is deduced as int
    // val == const int&
    std::cout << "(e): "; g2(ci);
    
    // (f)
    // argument is an rvalue; template parameter T is deduced as int
    // val == const int&
    std::cout << "(f): "; g2(i * ci);
    
    return 0;
}
```
