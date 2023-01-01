// Exercise 18.25:
/*
 Assume we have two base classes, Base1 and Base2, each of which defines a virtual member named print and a virtual destructor. From these base classes we derive the following classes, each of which redefines the print function:
 */

#include <iostream>

class Base1 {
public:
    Base1() { std::cout << "::Base1():" << std::endl; }
    
    virtual ~Base1() { std::cout << "~Base1()" << std::endl; }
    
    virtual void print() { std::cout << "Base1::print():" << std::endl; }
};

class Base2 {
public:
    Base2() { std::cout << "::Base2():" << std::endl; }
    
    virtual ~Base2() { std::cout << "~Base2()" << std::endl; }
    
    virtual void print() { std::cout << "Base2::print():" << std::endl; }
};

class D1 : public Base1 {
public:
    using Base1::Base1;
    D1() { std::cout << "Base1::D1():" << std::endl; }
    
    ~D1() { std::cout << "~D1()" << std::endl; }
    
    void print() override { std::cout << "Base1::D1::print():" << std::endl; }
};

class D2 : public Base2 {
public:
    using Base2::Base2;
    D2() { std::cout << "Base2::D2():" << std::endl; }
    
    ~D2() { std::cout << "~D2()" << std::endl; }
    
    void print() override { std::cout << "Base2::D2::print():" << std::endl; }
};

class MI : public D1, public D2 {
public:
    using D1::D1;
    using D2::D2;
    MI() { std::cout << "(Base1::D1 | Base2::D2)::MI()" << std::endl; }
    
    ~MI() { std::cout << "~MI()" << std::endl; }
    
    void print() final { std::cout << "(Base1::D1 | Base2::D2)::MI::print():" << std::endl; }
};

/*
 Using the following pointers, determine which function is used in each call:
 */

int main()
{
    Base1 *pb1 = new MI;
    Base2 *pb2 = new MI;
    D1 *pd1 = new MI;
    D2 *pd2 = new MI;
    
    std::cout << "\n";
    
    // (a)
    // guess: pb1 is type Base1, but MI is one of its derivatives -> MI::print()
    pb1->print();
    std::cout << "\n";
    // (Base1::D1 | Base2::D2)::MI::print():
    
    // (b)
    // guess: as above, in fact, I think they will all be MI, beacuse there all linked
    pd1->print();
    std::cout << "\n";
    // (Base1::D1 | Base2::D2)::MI::print():
    
    // (c)
    pd2->print();
    std::cout << "\n";
    // (Base1::D1 | Base2::D2)::MI::print():
    
    
    // (d)
    // call the destructors in reverse order
    // ~MI() -> ~D2() -> ~Base2()
    delete pb2;
    std::cout << "\n";
    // output:
    // ~MI()
    // ~D2()
    // ~Base2()
    // ~D1()
    // ~Base1()
    
    // (e)
    // ~MI() -> ~D1()
    delete pd1;
    std::cout << "\n";
    // output:
    // ~MI()
    // ~D2()
    // ~Base2()
    // ~D1()
    // ~Base1()
    
    // (f)
    // ~MI() -> ~D2()
    delete pd2;
    std::cout << "\n";
    // output:
    // ~MI()
    // ~D2()
    // ~Base2()
    // ~D1()
    // ~Base1()
    
    return 0;
}
