// Exercise 17.35:
/*
 Write a version of the program from page 758, that printed the square root of 2 but this time print hexadecimal digits in uppercase.
*/

#include <iostream>
#include <cmath>

int main()
{
    std::cout << "sqrt(2.0): "
              << std::hexfloat << std::showbase << std::uppercase
              << sqrt(2.0)
              << std::nouppercase << std::noshowbase << std::defaultfloat
              << std::endl;
    
    return 0;
}
