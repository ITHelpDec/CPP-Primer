// Exercise 18.27:
/*
 Given the class hierarchy in the box on page 810 and assuming we add a function named foo to MI as follows:
*/

// int ival;
// double dval;
// >> do you want these to be added to MI as private? protected? are they global?
//
// void MI::foo(double cval)
// {
//     int dval;
//     // exercise questions occur here
// }

/*
 (a) List all the names visible from within MI::foo.
 (b) Are any names visible from more than one base class?
 (c) Assign to the local instance of dval the sum of the dval member of Base1 and the dval member of Derived.
 (d) Assign the value of the last element in MI::dvec to Base2::fval.
 (e) Assign cval from Base1 to the first character in sval from Derived.
*/

#include <string>
#include <vector>
#include <iostream>

struct Base1 {
    void print(int) const { std::cout << ival << std::endl; }
protected:
    int    ival = 1;
    double dval = 1.1;
    char   cval = 'a';
private:
    int *id = &ival;
};

struct Base2 {
    void print(double) const { std::cout << fval << std::endl; }
protected:
    double  fval = 2.2;
private:
    double  dval = 2.2;
};

struct Derived : public Base1 {
    using Base1::Base1;
    
    void print(std::string sval) const { std::cout << sval << std::endl; }
protected:
    std::string sval = "3";
    double      dval = 3.3;
};

struct MI : public Derived, public Base2 {
    using Derived::Derived;
    using Base2::Base2;
    
    void print(std::vector<double>) const;
    
    // from previous exercise
    void print(int x) { std::cout << x << std::endl; }
    
    // exercises (a) - (e)
    void foo_a(double cval);
    void foo_b(double cval);
    void foo_c(double cval);
    void foo_d(double cval);
    void foo_e(double cval);
    
protected:
    int *ival;
    std::vector<double> dvec = { 1.1, 2.2, 3.3, 4.4, 5.5 };
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// .:. all possible members .:.
//
// Base1::ival (protected)
// Base1::dval (protected)
// Base1::cval (protected)
// Base1::*id (private)
//
// Base2::fval (protected)
// Base2::dval (private)
//
// Base1::Dervied::sval (protected)
// Base1::Derived::dval (protected)
//
// Base2::MI::*ival (protected)
// Base2::MI::dvec (protected)
// Base2::MI::foo(cval) { dval; } (function params)
//
// ::ival (global)
// ::dval (global)

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int ival = 42;
double dval = 6.9;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// (a)
// List all the names visible from within MI::foo.
// ...everything apart from the private members
void MI::foo_a(double cval)
{
    int dval = 69;
    std::cout << "Base2::MI::foo(cval): " << cval << "\n";
    std::cout << "Base2::MI::foo(cval)::dval: " << dval << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Base1::ival (protected) - yes
    std::cout << "Base1::ival: " << Base1::ival << "\n";
    
    // Base1::dval (protected) - yes
    std::cout << "Base1::dval: " << Base1::dval << "\n";
    
    // Base1::cval (protected) - yes
    std::cout << "Base1::cval: " << Base1::cval << "\n";
    
    // Base1::*id (private) - no (private)
    // std::cout << "*Base1::id: " << *Base1::id << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Base2::fval (protected) - yes
    std::cout << "Base2::fval: " << Base2::fval << "\n";
    
    // Base2::dval (private) - no (private)
    // std::cout << "Base2::dval: " << Base2::dval << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Base1::Dervied::sval (protected) - yes
    std::cout << "Base1::Derived::sval: " << Derived::sval << "\n";
    
    // Base1::Derived::dval (protected) - yes
    std::cout << "Base1::Derived::dval: " << Derived::dval << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Base2::MI::*ival (protected) - yes (needs to be referenced though)
    std::cout << "*Base2::MI::ival: " << MI::ival << "\n";
    
    // Base2::MI::dvec (protected) = yes
    std::cout << "*Base2::MI::dval: ";
    for (const auto &e : MI::dvec) { std::cout << e << " "; } std::cout << "\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // ::ival (global) - yes
    std::cout << "::ival: " << ::ival << "\n";
    
    // ::dval (global) - yes
    std::cout << "::dval: " << ::dval << std::endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// (b)
// Are any names visible from more than one base class?
// yes – see MI::foo_a()
void MI::foo_b(double cval)
{
    int dval = 69;
    std::cout << "yes – see above" << std::endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// (c)
// Assign to the local instance of dval the sum of the dval member of Base1 and the dval member of Derived.
void MI::foo_c(double cval)
{
    int dval = Base1::dval + Derived::dval;
    std::cout << Base1::dval << " + " << Derived::dval << " = " << dval << std::endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// (d)
// Assign the value of the last element in MI::dvec to Base2::fval.
void MI::foo_d(double cval)
{
    int dval;
    std::cout << "before: ";
    for (const auto &e : dvec) { std::cout << e << " "; } std::cout << "\n";
    
    dvec.back() = Base2::fval;
    
    std::cout << "after: ";
    for (const auto &e : dvec) { std::cout << e << " "; } std::cout << std::endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// (e)
// Assign cval from Base1 to the first character in sval from Derived.
void MI::foo_e(double cval)
{
    int dval;
    std::cout << "before: \n";
    std::cout << "Base1::cval: " << Base1::cval << ", "
    << "Derived::sval: " << Derived::sval << "\n";
    
    Derived::sval.front() = Base1::cval;
    
    std::cout << "after: \n";
    std::cout << "Base1::cval: " << Base1::cval << ", "
    << "Derived::sval: " << Derived::sval << "\n";
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main()
{
    std::cout << "(a)\n";
    MI().foo_a(3.1415926536);   // π    archimedes
    std::cout << "\n";
    
    std::cout << "(b)\n";
    MI().foo_b(-1);             // √-1  imaginary
    std::cout << "\n";
    
    std::cout << "(c)\n";
    MI().foo_c(2.7182818284);   // e    euler
    std::cout << "\n";
    
    std::cout << "(d)\n";
    MI().foo_d(1.41429);        // √2   pythagoras
    std::cout << "\n";
    
    std::cout << "(e)\n";
    MI().foo_e(1.7320508075);   // √3   theodorus
    std::cout << "\n";
    
    return 0;
}

// output:
//
// (a)
// Base2::MI::foo(cval): 3.14159
// Base2::MI::foo(cval)::dval: 69
// Base1::ival: 1
// Base1::dval: 1.1
// Base1::cval: a
// Base2::fval: 2.2
// Base1::Derived::sval: 3
// Base1::Derived::dval: 3.3
// *Base2::MI::ival: 0x0
// *Base2::MI::dval: 1.1 2.2 3.3 4.4 5.5
// ::ival: 42
// ::dval: 6.9
//
// (b)
// yes
//
// (c)
// 1.1 + 3.3 = 4
//
// (d)
// before: 1.1 2.2 3.3 4.4 5.5
// after: 1.1 2.2 3.3 4.4 2.2
//
// (e)
// before:
// Base1::cval: a, Derived::sval: 3
// after:
// Base1::cval: a, Derived::sval: a
//
// Program ended with exit code: 0
