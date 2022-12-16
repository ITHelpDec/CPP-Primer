# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (16/12/2022) .:.

```cpp
// Exercise 16.53:
/*
 Write your own version of the print functions and test them by printing one, two, and five arguments, each of which should have different types.
*/

#include <iostream>
#include <string>

template <typename T> std::ostream& print(std::ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename ...Args>
std::ostream& print(std::ostream &os, const T &t, const Args& ...rest) {
    os << t << " ";
    return print(os, rest...);
}

int main()
{
    int i = 1;
    double d = 3.14;
    std::string s = "manbearpig";
    
    std::cout << "print(1 arg):  ";
    print(std::cout, 42);
    std::cout << std::endl;
    
    std::cout << "print(2 args): ";
    print(std::cout, "hi", d);
    std::cout << std::endl;
    
    std::cout << "print(5 args): ";
    print(std::cout, i, d, s, 2, "halfmanhalfbearhalfpig");
    std::cout << std::endl;
    
    return 0;
}
```
```
print(1 arg):  42
print(2 args): hi 3.14
print(5 args): 1 3.14 manbearpig 2 halfmanhalfbearhalfpig
Program ended with exit code: 0
```
