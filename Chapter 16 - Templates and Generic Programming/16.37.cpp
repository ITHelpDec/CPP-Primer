// Exercise 16.37:
/*
 The library max function has two function parameters and returns the larger of its arguments.
 This function has one template type parameter.
 Could you call max passing it an int and a double?
 If so, how? If not, why not?
*/

#include <iostream>
#include <algorithm>

int main()
{
    int i = 3;
    double d = 0.14;
    
    // in ints standard form, no ("no matching call to max")
    // std::cout << std::max(i, d) << std::endl;
    
    // you could, however, call this...
    std::cout << std::max<int>(i, d) << std::endl;
    
    // ...or this...
    std::cout << std::max<double>(i, d) << std::endl;
    
    // ...or any other explicit template argument
    std::cout << std::max<long long>(i, d) << std::endl;
    
    return 0;
}
