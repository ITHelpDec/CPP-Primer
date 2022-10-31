// Exercise 15.23:
/*
 Assuming class D1 on page 620 had intended to override its inherited fcn function, how would you fix that class?
 Assuming you fixed the class so that fcn matched the definition in Base, how would the calls in that section be resolved?
*/

#include <iostream>

class Base {
public:
    virtual int fcn() { return 123; }
};

class D1 : public Base {
public:
    // (2)
    int fcn(int);
    virtual void f2();
    // (1) void f2();
    
    // if intention was to override inherited fcn()
    int fcn() override { return 456; }
};

class D2 : public D1 {
public:
    int fcn(int);
    int fcn();
    void f2();
};

int main()
{
    D1 d1obj;
    D1 *d1p = &d1obj;
    
    // no issue with object
    std::cout << d1obj.fcn() << std::endl;
    
    // Undefined symbol: vtable for D1
    // we can choose to remove the other virtual function with D1 it we want this to run
    // std::cout << d1p->fcn() << std::endl;
    
    // otherwise, we can use the scope operator for D1 to remove ambiguity
    std::cout << d1p->D1::fcn() << std::endl;
    
    // or just change the fcn(int) function at marker 2, such that the function holds no arguments and uses "override"
    
    return 0;
}
