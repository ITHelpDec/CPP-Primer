// Exercise 15.14:
/*
 Given the classes from the previous exercise and the following objects, determine which function is called at run time:
*/

#include <string>
#include <iostream>

class Base {
public:
    Base() = default;
    
    std::string name() { return basename; }
    
    virtual void print(std::ostream &os) { os << basename; }
private:
    std::string basename = "manbearpig";
};

class Derived : public Base {
public:
    void print(std::ostream &os) { Base::print(os); os << " " << i << std::endl; }
private:
    int i = 1;
};

int main()
{
    Base bobj;
    Base *bp1 = &bobj;
    Base &br1 = bobj;
    
    Derived dobj;
    Base *bp2 = &dobj;
    Base &br2 = dobj;
    
    // (a) - Base
    bobj.print(std::cout);
    std::cout << std::endl;
    
    // (b)- Derived
    dobj.print(std::cout);
    
    // (c) - Base
    std::cout << bp1->name() << std::endl;
    
    // (d) - Base
    std::cout << bp2->name() << std::endl;
    
    // (e) - Base
    br1.print(std::cout);
    std::cout << std::endl;
    
    // (f) - Derived
    br2.print(std::cout);
    
    return 0;
}
