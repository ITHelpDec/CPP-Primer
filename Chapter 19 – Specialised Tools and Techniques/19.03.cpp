// Exercise 19.03:
/*
 Given the following class hierarchy in which each class defines a public default constructor and virtual destructor:
*/

// no virtual inheritance?
class A; class B; class C; class D;

/*
 which, if any, of the following dynamic_casts fail?
*/

#include <iostream>

class A {
public:
    A() = default;
    virtual ~A() { }
};

class B : virtual public A {
public:
    B() : A() { }
    virtual ~B() { }
};

// created create a "resolvable" A to avoid the ambiguity error below
// otherwise, use virtual inheritance at the cose of a little more run-time overhead
//
// class ResolvableA : virtual public A {
// public:
//     ResolvableA() : A() { }
//     virtual ~ResolvableA() { }
// };
//

class C : public B {
public:
    C() : B() { }
    virtual ~C() { }
};

// warning: Direct base 'A' is inaccessible due to ambiguity:
class D : public B, virtual public A {
public:
    D() : B(), A() { }
    virtual ~D() { }
};

// version without virtual inheritance
//
// class D : public B, public ResolvableA {
// public:
//     D() : B(), ResolvableA() { }
//     virtual ~D() { }
// };
//

int main()
{
    // (a)
    A *pa_c = new C;
    if (B *pb = dynamic_cast< B* >(pa_c)) {
        std::cout << "good cast" << "\n";
    } else {
        std::cerr << "bad_cast" << "\n";
    } // good cast
    
    // (b)
    B *pb = new B;
    if (C *pc = dynamic_cast< C* >(pb)) {
        std::cout << "good cast" << "\n";
    } else {
        std::cerr << "bad_cast" << "\n";
    } // bad_cast
    
    // (c) - won't work
    A *pa_d = new D;
    if (B *pb = dynamic_cast< B* >(pa_d)) {
        std::cout << "good cast" << "\n";
    } else {
        std::cerr << "bad_cast" << "\n";
    } // good cast
    
    // seems to only cast well when dynamic_cast types are less derived than the expression
    
    // and not sure why the book isn't encouraging the deallocation of heap variables memory
    delete pa_c; delete pb; delete pa_d;
    
    return 0;
}
