// Exercise 13.46:
/*
 Which kind of reference can be bound to the following initializers?
 
 >> Question probably should have mentioned to replace the quesiton marks with relevant & or &&
*/

#include <vector>
#include <iostream>

int f() { return 1; }

int main()
{
    std::vector<int> vi(100);
    
    int &&r1 = f();
    std::cout << r1 << std::endl;
    // returns non-reference; f() is also a temporary
    
    int &r2 = vi[0];
    std::cout << r2 << std::endl;
    // subscript, so lvalue
    
    int &r3 = r1;
    std::cout << r3 << std::endl;
    // r3 refers to r1
    
    int &&r4 = vi[0] * f();
    // arithmetic operator creates rvalue reference
    
    return 0;
}
