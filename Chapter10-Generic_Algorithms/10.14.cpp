// Exercise 10.14:
/*
 Write a lambda that takes two ints and returns their sum.
*/

#include <iostream>

int main()
{
    // create lambda function
    auto sum = [] (int &x, int &y) { return x + y; };
    
    // create variables
    int a = 5, b = 6;
    
    // output result
    std::cout << a << " + " << b << " = " << sum(a, b) << std::endl;
    
    return 0;
}
