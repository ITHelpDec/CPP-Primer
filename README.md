# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (16/12/2022) .:.

```cpp
// Exercise 16.55:
/*
 Explain how the variadic version of print would execute if we de- clared the nonvariadic version of print after the definition of the variadic version.
*/

// It will try call...

// print(std::ostream &os, const T &t) { /*...*/ }

// ...but this hasn't be declared yet.

// We could fix this by declaring the function early without defining it.

#include <iostream>
#include <string>
#include <vector>

// early declaration of non-variadic "print" version
template <typename T> std::ostream& print(std::ostream&, const T&);

template <typename T, typename ...Args> std::ostream& print(std::ostream &os, const T &t, const Args& ...rest) {
    std::cout << "\nvariadic: ";
    os << t << " ";
    return print(os, rest...);
}

// definition
template <typename T> std::ostream& print(std::ostream &os, const T &t) {
    std::cout << "\nnon-variadic: ";
    return os << t;
}

int main()
{
    int i = 1;
    double d = 3.14;
    std::string s = "manbearpig";
    
    std::cout << "print(1 arg):  ";
    print(std::cout, 42) << "\n\n";
    
    std::cout << "print(2 args): ";
    print(std::cout, "hi", d) << "\n\n";
    
    std::cout << "print(5 args): ";
    print(std::cout, i, d, s, 2, "halfmanhalfbearhalfpig") << "\n\n";
    
    std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    
    std::cout << "print(ivec):  ";
    for (const auto &e : ivec) {
        print(std::cout, e) << " ";
    } std::cout << std::endl;
    
    return 0;
}
```
```
output:
print(1 arg):  
non-variadic: 42

print(2 args): 
variadic: hi 
non-variadic: 3.14

print(5 args): 
variadic: 1 
variadic: 3.14 
variadic: manbearpig 
variadic: 2 
non-variadic: halfmanhalfbearhalfpig

print(ivec):  
non-variadic: 1 
non-variadic: 2 
non-variadic: 3 
non-variadic: 4 
non-variadic: 5 
Program ended with exit code: 0
```
