// Exercise 19.04:
/*
 Using the classes defined in the first exercise, ...
 ...rewrite the following code to convert the expression *pa to the type C&:
 
 if (C *pc = dynamic_cast< C* >(pa)) {
     // use C’s members
 } else {
     // use A’s members
 }
 
 >> another not-so-great / vague question
 >> a lot of these code samples seem to be supplied without context
 >> RTTI doesn't seem to have the best impression (it's frowned on by Google, at least), ...
 >> ...but a better understanding as to why would be more helpful
 
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

class C : public B {
public:
    C() : B() { }
    virtual ~C() { }
};

class D : public B, virtual public A {
public:
    D() : B(), A() { }
    virtual ~D() { }
};

// we cannot use the if-else pointer method when it comes to const references
// "When a cast to a reference type fails, the cast throws a std::bad_cast exception" – pg. 826
//
// "If bp (t) points (refers) to a Derived (const C&) object, then the cast will ...
// ...initialize dp (t) to point (refer) to the Derived (const C&) object to which bp (t) points (refers)"

// creating a template helps to genericise our solution for multiple class types
template <class T> void f(const T &t) {
    try {
        // use C's members
        const C &c = dynamic_cast<const C&>(t);
        std::cout << "success: using C's members\n" << std::endl;
    } catch (const std::bad_cast &e) {
        std::cerr << e.what() << ": using A's members\n" << std::endl;
        // use A's members
        const A &a = dynamic_cast<const A&>(t);
    }
}

int main()
{
    A a;
    std::cout << "Attempting dynamic_cast with \"A a\"\n"; f(a);
    
    B b;
    std::cout << "Attempting dynamic_cast with \"B b\"\n"; f(b);
    
    C c;
    std::cout << "Attempting dynamic_cast with \"C c\"\n"; f(c);
    
    D d;
    std::cout << "Attempting dynamic_cast with \"D d\"\n"; f(d);
    
    return 0;
}

// output:

// Attempting dynamic_cast with "A a"
// std::bad_cast: using A's members

// Attempting dynamic_cast with "B b"
// std::bad_cast: using A's members

// Attempting dynamic_cast with "C c"
// success: using C's members

// Attempting dynamic_cast with "D d"
// std::bad_cast: using A's members

// Program ended with exit code: 0
