// Exercise 10.21:
/*
 Write a lambda that captures a local int variable and decrements that variable until it reaches 0.
 Once the variable is 0 additional calls should no longer decrement the variable.
 The lambda should return a bool that indicates whether the captured variable is 0.
*/

#include <iostream>

int main()
{
    int x = 14;
    
    // lambda captures local value x by reference (loops beyond if capture is explicit)
    auto is_zero = [&x] () { return x == 0 ? true : false; };
    
    while (!is_zero()) {
        std::cout << x << " ";
        --x;
    }
    
    std::cout << "\nx has now reached " << x << std::endl;
    
    return 0;
}
