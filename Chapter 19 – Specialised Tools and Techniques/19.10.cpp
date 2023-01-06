// Exercise 19.10:
/*
 Given the following class hierarchy in which each class defines a...
 public default constructor and virtual destructor, ...
 ...which type name do the following statements print?
*/

#include <iostream>

class A {
public:
    A() = default;
    virtual ~A() { }
};

class B : public A {
public:
    B() : A() { }
    virtual ~B() { }
};

class C : public B {
public:
    C() : B() { }
    virtual ~C() { }
};

int main()
{
    // (a)
    A *pa = new C;
    std::cout << "typeid(pa): \"" << typeid(pa).name() << "\"" << std::endl;
    // guess:  A pointer (only C pointer when dereferenced)
    // output: P1A (pointer-to-A)
    
    std::cout << "checking...";
    if (typeid(pa) == typeid(A*))
        std::cout << "yup, it's an A*\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // (b)
    C cobj;
    A& ra = cobj;
    std::cout << "typeid(&ra): \"" << typeid(&ra).name() << "\"" << std::endl;
    // guess:  C ("&" operator was used)
    // output: P1A! (pointer-to-a) => T *t == Y &y?
    
    std::cout << "checking...";
    if (typeid(&ra) == typeid(A*))
        std::cout << "yup, it's an A*\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // (c)
    B *px = new B;
    // A& ra = *px;
    // don't use same-name variables in an exercise...
    A& rra = *px;
    std::cout << "typeid(rra): \"" << typeid(rra).name() << "\"" << std::endl;
    // guess:  B* (px is of type B; px dereferenced is a dynamically-allocated B)
    // output: 1B (i.e. "B", not B*)
    
    std::cout << "checking...";
    if (typeid(rra) == typeid(B))
        std::cout << "yup, it's a B\n" << std::endl;
    
    return 0;
}

// output:
// typeid(pa): "P1A"
// checking...yup, it's an A*
//
// typeid(&ra): "P1A"
// checking...yup, it's an A*
//
// typeid(rra): "1B"
// checking...yup, it's a B
//
// Program ended with exit code: 0
