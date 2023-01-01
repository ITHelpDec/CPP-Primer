// Exercise 18.29:
/*
 Given the following class hierarchy:
 
 // class Class { ... };
 // class Base : public Class { ... };
 // class D1 : virtual public Base { ... };
 // class D2 : virtual public Base { ... };
 // class MI : public D1, public D2 { ... }; class Final : public MI, public Class { ... };
 
 
 (a) In what order are constructors and destructors run on a Final object?
 (b) A Final object has how many Base parts? How many Class parts?
 (c) Which of the following assignments is a compile-time error?
 
 >>> Base *pb;
 >>> Class *pc;
 >>> MI *pmi;
 >>> D2 *pd2;
 
 (a) pb = new Class;
 (b) pc = new Final;
 (c) pmi = pb;
 (d) pd2 = pmi;
 
*/

// Let's define our classes...

#include <iostream>

class Class {
public:
    Class() { std::cout << "Class()" << std::endl; }
};

class Base : public Class {
public:
    Base() { std::cout << "Class::Base()" << std::endl; }
};

class D1 : virtual public Base {
public:
    D1() { std::cout << "virtual Base::D1()" << std::endl; }
};

class D2 : virtual public Base {
public:
    D2() { std::cout << "virtual Base::D2()" << std::endl; }
};

class MI : public D1, public D2 {
public:
    MI() { std::cout << "(Base::D1 | Base::D1)::MI()" << std::endl; }
};

// error: "Direct base 'Class' is inaccessible due to ambiguity:"
class Final : public MI, public Class {
public:
    Final() { std::cout << "((Base::D1 | Base::D1)::MI() | Class())" << std::endl; }
};

int main()
{
    Final countdown;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // (a) In what order are constructors and destructors run on a Final object?
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Class()
    // Class::Base()
    // virtual Base::D1()
    // virtual Base::D2()
    // (Base::D1 | Base::D1)::MI()
    // Class()
    // ((Base::D1 | Base::D1)::MI() | Class())
    
    // I'd have thought the virtual functions would be constructed first...
    //
    // "The direct base classes are examined in declaration order to determine...
    // ...whether there are any virtual base classes.
    // If so, the virtual bases are constructed first, ...
    // ...followed by the nonvirtual base-class constructors in declaration order.
    // pg. 815
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // (b) A Final object has how many Base parts? How many Class parts?
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // see above
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // (c) Which of the following assignments is a compile-time error?
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    Base *pb;
    Class *pc;
    MI *pmi;
    D2 *pd2;
    
    // (a)
    // pb = new Class;
    // error: "Incompatible pointer types assigning to 'Base *' from 'Class *'"
    
    // (b)
    // pc = new Final;
    // error: "Ambiguous conversion from derived class 'Final' to base class 'Class':"
    
    // (c)
    // pmi = pb;
    // error: "Incompatible pointer types assigning to 'MI *' from 'Base *'"
    
    // (d)
    pd2 = pmi;
    // no errors assigning to D2* from MI*, as MI is a derivative of D2
    
    return 0;
}
