# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (17/12/2022) .:.

```cpp
// Exercise 16.58:
/*
 Write the emplace_back function for your StrVec class and for the Vec class that you wrote for the exercises in § 16.1.2 (p. 668).
*/

#include "StrVec.hpp"
#include "Vec.h"
#include <iostream>

void testStrVec(StrVec &svec) {
    svec.emplace_back("manbearpig");
    
    std::string s1 = "half";
    std::string s2 = "man";
    
    svec.emplace_back(10, 'c');
    
    svec.emplace_back(s1 + " " + s2);
}

template <typename T> void testVec(Vec<T> &tvec) {
    tvec.emplace_back(0);
    
    int i = 1;
    
    tvec.emplace_back(i);
    
    tvec.emplace_back(i + i);
}

int main()
{
    StrVec svec;
    testStrVec(svec);
    printVec(svec);

    std::cout << std::endl;
    
    Vec<int> ivec;
    testVec(ivec);
    printVec(ivec);
    
    return 0;
}
```
```
output:
Printing vector...
"manbearpig" "cccccccccc" "half man" 

Printing vector...
"0" "1" "2" 
Program ended with exit code: 0
```
