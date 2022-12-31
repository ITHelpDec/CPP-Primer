// Exercise 18.23:
/*
 Using the hierarchy in exercise 18.22 along with class D defined below,...
 ...and assuming each class defines a default constructor,...
 ...which, if any, of the following conversions are not permitted?
 */

#include <iostream>

class A {
public:
    A() { std::cout << "::A()" << std::endl; }
    char memA = 'A';
};

class B : public A {
public:
    using A::A;
    B() { std::cout << "A::B()" << std::endl; }
    char memB = 'B';
};

class C : public B {
public:
    using B::B;
    C() { std::cout << "A::B::C()" << std::endl; }
    char memC = 'C';
};

class X {
public:
    X() { std::cout << "::X()" << std::endl; }
    char memX = 'X';
};

class Y {
public:
    Y() { std::cout << "::Y()" << std::endl; }
    char memY = 'Y';
};
class Z : public X, public Y {
public:
    using X::X;
    using Y::Y;
    Z() { std::cout << "(::X | ::Y)::Z()" << std::endl; }
    char memZ = 'Z';
};

class MI : public C, public Z {
public:
    using C::C;
    using Z::Z;
    MI() { std::cout << "(::C | ::Z)::MI()" << std::endl; }
    std::string memMI = "MI";
};

class D : public X, public C {
public:
    D() { std::cout << "(::X | ::C)::D()" << std::endl; }
    char memD = 'D';
};

int main()
{
    std::cout << ".:. D constructors .:.\n";
    D *pd = new D;
    
    // ::X()
    // ::A()
    // A::B()
    // A::B::C()
    // (::X | ::C)::D()
    
    // why not use smart pointers?
    // auto pd = std::make_shared<D>();
    
    std::cout << "\n.:. inherited members .:.\n";
    
    std::cout << "*pd: " << pd->memA << " " << pd->memB << " "<< pd->memC << " " << pd->memX << " "
    // << pd->memY << " "<< pd->memZ << " " << pd->memMI << " "
    << pd->memD << std::endl;
    
    // (a) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    X *px = pd;
    std::cout << "*px: " // << px->memA << " " << px->memB << " " << px->memC << " "
    << px->memX << " "
    // << px->memY << " " << px->memZ << " " << px->memMI << " " << px->memD
    << std::endl;
    
    // (b) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    A *pa = pd;
    std::cout << "*pa: " << pa->memA << " "
    // << pa->memB << " " << pa->memC << " " << pa->memX << " " << pa->memY << " "
    // << pa->memZ << " " << pa->memMI << " " << pa->memD
    << std::endl;
    
    // (c) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    B *pb = pd;
    std::cout << "*pb: " << pb->memA << " " << pb->memB << " "
    // << pb->memC << " " << pb->memX << " " << pb->memY << " "
    // << pb->memZ << " " << pb->memMI << " " << pb->memD
    << std::endl;
    
    // (d) - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    C *pc = pd;
    std::cout << "*pc: " << pc->memA << " " << pc->memB << " " << pc->memC << " "
    // << pc->memX << " " << pc->memY << " " << pc->memZ << " "
    // << pc->memMI << " " << pc->memD
    << std::endl;
    
    // - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // don't forget to delete dynamically-allocated memory...
    delete pd;
    
    return 0;
}

// output:
// .:. D constructors .:.
// ::X()
// ::A()
// A::B()
// A::B::C()
// (::X | ::C)::D()
//
// .:. inherited members .:.
// *pd: A B C X D
// *px: X
// *pa: A
// *pb: A B
// *pc: A B C
// Program ended with exit code: 0
