// Exercise 7.58:
/*
 Which, if any, of the following static data member declarations and
 definitions are errors?
 Explain why.
 
 // example.h
 class Example
    {
 public:
    static double rate = 6.5;
    static const int vecSize = 20;
    static vector<double> vec(vecSize);
 };
 
 // example.C
 #include "example.h"
 double Example::rate;
 vector<double> Example::vec;
 
*/

#include <vector>

class Example {
public:
    // static double rate = 6.5;
    // non-const must be initialised out-of-line
    static double rate;
    static const int vecSize = 20;
    
    // static std::vector<double> vec(vecSize);
    // cannot use parenthesis for in-class initialiser
    // again, static members should be initialised outside of class body
    static std::vector<double> vec;
};

// rate initialised out of line; static already declared in body of class
double Example::rate = 6.5;
// same for Example::vec
std::vector<double> Example::vec(vecSize);
