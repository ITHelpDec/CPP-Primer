// Exercise 17.36:
/*
 Modify the program from the previous exercise to print the various floating-point values so that they line up in a column.
*/

#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
    std::cout << ">>> sqrt(2.0) <<<\n"
              << "base" << std::setw(24) << "floating-point values\n"
              << std::hexfloat << std::showbase << std::uppercase
              << std::setw(24) << std::internal
              << sqrt(2.0)
              << std::nouppercase << std::noshowbase << std::defaultfloat
              << std::endl;
    
    return 0;
}
