// Exercise 18.30:
/*
 Define a default constructor, a copy constructor, and a constructor that has an int parameter in Base.
 
 Define the same three constructors in each derived class.
 
 Each constructor should use its argument to initialize its Base part.
 
*/

#include <iostream>

class Class {
public:
    Class () = default;
};

class Base : public Class {
public:
    // "Define a detault constructor, ..."
    Base() = default;
    
    // "...a copy constructor, ..."
    Base(const Base &b) : base_int_(b.base_int_) { }
    
    // "...and a constructor that has an..."
    Base(int x) : base_int_(x) { }
protected:
    // "...int parameter in Base."
    int base_int_ = 69;
};

class D1 : virtual public Base {
public:
    // "Define the same three constructors in each derived class..."
    D1() : Base() { }
    D1(const D1 &d) : Base(d) { }
    // D1(const D1 &d) { *this = d; } also works
    
    // "Each constructor should use its argument to initialize its Base part."
    D1(int x) : Base(x) { }
};

class D2 : virtual public Base {
public:
    D2() : Base() { }
    D2(const D2 &d) : Base(d) { }
    // D2(const D2 &d) { *this = d; }
    
    D2(int x) : Base(x) { }
};

class MI : public D1, public D2 {
public:
    MI() : D1(), D2() { }
    MI(const MI &mi) : Base(mi), D1(mi), D2(mi) { }
    // MI(const MI &mi) { *this = mi; }
    
    MI(int x) : Base(x), D1(x), D2(x) { }
};

// error: "Direct base 'Class' is inaccessible due to ambiguity:"
class Final : public MI, public Class {
public:
    Final() : Base(), MI(), Class() { }
    Final(const Final &f) : Base(f), MI(f) { }
    // Final(const Final &f) { *this = f; }
    
    // Final(int x) : Base(x), D1(x), D2(x), MI(x) { }
    // error: "Type 'D1' is not a direct or virtual base of 'Final'"
    // don't need to explicitly call D1 and D2 – MI combines then
    
    Final(int x) : Base(x), MI(x) { }
    
    // test function to see if Base::base_int_ has changed
    int print() { return Base::base_int_; }
};

int main()
{
    int x = 3;
    std::cout << "x: " << x << std::endl;
    
    std::cout << "Creating \"Final\" member called \"countdown\" using \"x\"...\n";
    Final countdown(x);
    
    std::cout << "\nCalling Final::print() to see if Base::base_int_ has changed...\n";
    std::cout << "countdown.print(): " << countdown.print() << std::endl;
    
    std::cout << (countdown.print() == x ? "\nSuccess!" : "\nNo dice...") << std::endl;
    
    std::cout << "\nAnd what if we do a copy?\n";
    std::cout << "Creating \"Final\" member called \"dadadaaaa_daa\" using \"countdown\"...\n";
    Final dadadaaaa_daa(countdown);
    std::cout << "dadadaaaa_daa.print(): " << dadadaaaa_daa.print() << "\n" << std::endl;
    
    return 0;
}

// output:
// x: 3
// Creating "Final" member called "countdown" using "x"...
//
// Calling Final::print() to see if Base::base_int_ has changed...
// countdown.print(): 3
//
// Success!
//
// And what if we do a copy?
// Creating "Final" member called "dadadaaaa_daa" using "countdown"...
// dadadaaaa_daa.print(): 3
//
// Program ended with exit code: 0
