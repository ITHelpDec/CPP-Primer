// Exercise 18.26:
/*
 Given the hierarchy in the box on page 810, why is the following call to print an error?
 Revise MI to allow this call to print to compile and execute correctly.
 */

#include <string>
#include <vector>
#include <iostream>

struct Base1 {
    void print(int) const { std::cout << ival << std::endl; }
protected:
    int    ival;
    double dval;
    char   cval;
private:
    int *id;
};

struct Base2 {
    void print(double) const { std::cout << fval << std::endl; }
protected:
    double  fval;
private:
    double  dval;
};

struct Derived : public Base1 {
    using Base1::Base1;
    
    void print(std::string sval) const { std::cout << sval << std::endl; }
protected:
    std::string sval;
    double      dval;
};

struct MI : public Derived, public Base2 {
    using Derived::Derived;
    using Base2::Base2;
    
    void print(std::vector<double>) const { std::cout << *ival << std::endl; }
    
    // (2) -> output: 42
    void print(int x) { std::cout << x << std::endl; }
    
    // the below has popped up, but produces 0, so not what we want
    // void print(int x) { Base1::print(x); }
    
protected:
    int *ival;
    std::vector<double> dvec;
};

int main()
{
    MI mi;
    
    mi.print(42);
    // error: "No viable conversion from 'int' to 'std::vector<double>'"
    // MI::print() will be called, because there are no virtual functions
    
    // potential solutions:
    // (1) create virtual functions
    // (2) change the function to take an integer argument (or overload a new one)
    
    // didn't have much lucky with the virtual implementation, so opted for (2)
    
    return 0;
}
