// Exercise 15.13:
/*
 Given the following classes, explain each print function:
*/

#include <string>
#include <iostream>

class Base {
    
public:
    Base(const std::string &s) : basename(s) { }
    std::string name() { return basename; }
    
    // creates template, printing basename
    virtual void print(std::ostream &os) { os << basename; }
private:
    std::string basename;
};

class Derived : public Base {
public:
    Derived(const std::string &s, int x) : Base(s), i(x) { }
    
    // void print(std::ostream &os) { print(os); os << " " << i; }
    
    // the derived function above will be chosen at run-time
    // unless we can find a way to refer to the base function instead, this call will loop indefinitely
    // we can resolve this unwanted recursion by adding the "Base::" prefix to "print(os)"
    void print(std::ostream &os) { Base::print(os); os << " " << i << std::endl; }
private:
    int i;
};

int main()
{
    Base b("manbearpig");
    Derived d("manbearpig", 1);
    
    b.print(std::cout); std::cout << std::endl;
    d.print(std::cout);
    
    return 0;
}
