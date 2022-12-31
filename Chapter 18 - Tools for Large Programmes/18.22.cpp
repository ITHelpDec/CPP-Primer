// Exercise 18.22:
/*
 Given the following class hierarchy (in which, each class defines a default constructor)...
 
 class A { ... };
 class B : public A { ... };
 class C : public B { ... };
 class X { ... };
 class Y { ... };
 class Z : public X, public Y { ... }; class MI : public C, public Z { ... };
 
 ...what is the order of constructor execution for the following definition?
 
 MI mi;
 
 */

#include <iostream>

class A {
public:
    A() { std::cout << "::A()" << std::endl; }
};

class B : public A {
public:
    using A::A;
    B() { std::cout << "A::B()" << std::endl; }
};

class C : public B {
public:
    using B::B;
    C() { std::cout << "A::B::C()" << std::endl; }
};

class X {
public:
    X() { std::cout << "::X()" << std::endl; }
};

class Y {
public:
    Y() { std::cout << "::Y()" << std::endl; }
};
class Z : public X, public Y {
public:
    using X::X;
    using Y::Y;
    Z() { std::cout << "(::X | ::Y)::Z()" << std::endl; }
};

class MI : public C, public Z {
public:
    using C::C;
    using Z::Z;
    MI() { std::cout << "(::C | ::Z)::MI()" << std::endl; }
};

int main()
{
    std::cout << "Brace yourselves...creating an MI object...\n";
    
    MI mi;
    
    return 0;
}

// output:
// Brace yourselves...creating an MI object...
// ::A()
// A::B()
// A::B::C()
// ::X()
// ::Y()
// (::X | ::Y)::Z()
// (::C | ::Z)::MI()
// Program ended with exit code: 0
