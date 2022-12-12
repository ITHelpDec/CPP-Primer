# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (12/12/2022) .:.

```cpp
// Exercise 16.47:
/*
 Write your own version of the flip function and test it by calling functions that have lvalue and rvalue reference parameters.
*/

#include <iostream>
#include <utility>

void f(int v1, int &v2) {
    std::cout << v1 << " " << ++v2 << std::endl;
}

void g(int &&v1, int &v2) {
    std::cout << v1 << " " << v2 << std::endl;
}

template <typename F, typename T1, typename T2> void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}

template <typename F, typename T1, typename T2> void flip2(F f, T1 &&t1, T2 &&t2) {
    f(t2,t1);
}

template <typename F, typename T1, typename T2> void flip3(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

int main()
{
    int i = 3, j = 5;
    
    f(42, i);
    flip1(f, j, 42);
    flip2(f, j, 42);
    flip3(f, j, 42);
    
    g(42, i);
    // flip1(g, j, 42); // error: can't initialise T&& from lvalue
    // flip2(g, j, 42); // error: can't initialise T&& from lvalue
    flip3(g, j, 42);
    
    return 0;
}
```
