// Exercise 10.15:
/*
 Write a lambda that captures an int from its enclosing function and takes an int parameter.
 The lambda should return the sum of the captured int and the int parameter.
*/

#include <iostream>

int main()
{
    // create variables
    int a = 5, b = 5;
    
    // [a] = captured int
    // y = parameter int
    // {} = body of function
    auto add = [a] (int &anyint) { return a + anyint; };
    
    // don't need to explicitly call capture list, just the function
    std::cout << a << " + " << b << " = " << add(b) << std::endl;
    
    return 0;
}
