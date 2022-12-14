# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (13/12/2022) .:.

```cpp
// Exercise 16.48:
/*
 Write your own versions of the debug_rep functions.
*/

#include <string>
#include <sstream>
#include <iostream>

template <typename T> std::string debug_rep(const T &t) {
    std::cout << "debug_rep(const T &t) called" << std::endl;
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> std::string debug_rep(T *p) {
    std::cout << "debug_rep(T *p) called" << std::endl;
    
    std::ostringstream ret;
    ret << "pointer: " << p;
    
    if (p) { ret << " (" << debug_rep(*p) <<")"; }
    else { ret << " (null pointer)"; }
    
    return ret.str();
}

std::string debug_rep(const std::string &s) {
    std::cout << "debug_rep(const std::string &s) called" << std::endl;
    return '"' + s + '"';
}

std::string debug_rep(char *p) {
    std::cout << "debug_rep(char *p) called" << std::endl;
    return debug_rep(std::string(p));
}
                     
std::string debug_rep(const char *p) {
    std::cout << "debug_rep(const char *p) called" << std::endl;
    return debug_rep(std::string(p));
}

int main()
{
    std::string s1 = "manbearpig";
    std::cout << debug_rep(s1) << std::endl << std::endl;
    std::cout << debug_rep(&s1) << std::endl << std::endl;
    
    const std::string *s2 = &s1;
    std::cout << debug_rep(s2) << std::endl << std::endl;
    
    const std::string *s3 = nullptr;
    std::cout << debug_rep(s3) << std::endl << std::endl;
    
    const char *str = "c-style string";
    std::cout << debug_rep(str) << std::endl << std::endl;

    return 0;
}
```
```
output:
debug_rep(const std::string &s) called
"manbearpig"

debug_rep(T *p) called
debug_rep(const T &t) called
pointer: 0x7ff7bfeff1a8 (manbearpig)

debug_rep(T *p) called
debug_rep(const T &t) called
pointer: 0x7ff7bfeff1a8 (manbearpig)

debug_rep(T *p) called
pointer: 0x0 (null pointer)

debug_rep(const char *p) called
debug_rep(const std::string &s) called
"c-style string"

Program ended with exit code: 0
```
