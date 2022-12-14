# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (14/12/2022) .:.

```cpp
// Exercise 16.49:
/*
 Explain what happens in each of the following calls:
*/

#include <iostream>

template <typename T> void f(T);// { std::cout << "f(T)" << std::endl; }
template <typename T> void f(const T*);// { std::cout << "f(const T*)" << std::endl; }
template <typename T> void g(T);// { std::cout << "g(T)" << std::endl; }
template <typename T> void g(T*);// { std::cout << "g(T*)" << std::endl; }

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
```
```
output:
(a) g(T)
(b) g(T*)
(c) g(T)
(d) g(T*)
(e) f(T)
(f) f(T)
(g) f(T)
(h) f(const T*)
Program ended with exit code: 0```
