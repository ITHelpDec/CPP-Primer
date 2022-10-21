// Exercise 14.51:
/*
 Show the conversion sequences (if any) needed to call each version of calc and explain why the best viable function is selected.
*/

#include <iostream>

struct LongDouble {
    LongDouble(double = 0.0);
    operator double();
    operator float();
};

void calc(int) { std::cout << "(int) called" << std::endl; }

void calc(LongDouble) { std::cout << "(LongDouble) called)" << std::endl; }

int main()
{
    double dval;
    calc(dval); // whichcalc?
}

// void calc(int) will be called - easier to demote double to int (standard arithmetic type) than to user-defined class type
