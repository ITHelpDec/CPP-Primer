// Exercise 18.28:
/*
 Given the following class hierarchy, which inherited members can be accessed without qualification from within the VMI class?
 Which require qualification?
 Explain your reasoning.
*/

#include <iostream>
 
struct Base {
    void bar(int) { std::cout << "Base::bar(int)" << std::endl; }
protected:
    int ival = 1;
};
 
struct Derived1 : virtual public Base {
    void bar(char) { std::cout << "Base::Derived1::bar(char)" << std::endl; }
    void foo(char) { std::cout << "Base::Derived1::foo(char)" << std::endl; }
protected:
    char cval = 'a';
};
 
struct Derived2 : virtual public Base {
    void foo(int) { std::cout << "Base::Derived2::foo(int)" << std::endl; }
protected:
    int ival = 2;
    char cval = 'b';
};
 
class VMI : public Derived1, public Derived2 {
public:
    void printAllMembers();
};
 
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
 // .:. all available members .:.
 //
 // Base::bar(int) (public)
 // Base::ival (protected)
 //
 // Base::Dervied1::bar(char) (public)
 // Base::Dervied1::foo(char) (public)
 // Base::Dervied1::cval (protected)
 //
 // Base::Dervied2::foo(int) (public)
 // Base::Dervied2::ival (protected)
 // Base::Dervied2::cval (protected)
 //
 
 // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 
void VMI::printAllMembers()
{
    // Base::bar(int) (public) - yes
    Base::bar(5);
    
    // Base::ival (protected) - yes (must be qualified)
    std::cout << "Base::ival: " << Base::ival << "\n" << std::endl;
    
    // the following will return Derived2::ival (2)
    // std::cout << "Base::ival: " << ival << "\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     
    // Base::Dervied1::bar(char) (public) - yes
    Derived1::bar('x');
     
    // Base::Dervied1::foo(char) (public) - yes
    Derived1::foo('y');
     
    // Base::Dervied1::cval (protected) - yes (must be qualified)
    std::cout << "Derived1::cval: " << Derived1::cval << "\n" << std::endl;
     
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
     
     
    // Base::Derived2::foo(int) (public) - yes
    Derived2::foo(69);
     
    // Base::Derived2::ival (protected) - yes
    // as above with Derived2::ival
    std::cout << "Derived2::ival: " << Derived2::ival << std::endl;
     
    // Base::Derived2::cval (protected) - yes (must be qualified)
    std::cout << "Derived2::cval: " << Derived2::cval << "\n" << std::endl;
 }
 
int main()
{
    VMI().printAllMembers();
     
    return 0;
}

// output
// Base::bar(int)
// Base::ival: 1
//
// Base::Derived1::bar(char)
// Base::Derived1::foo(char)
// Derived1::cval: a
//
// Base::Derived2::foo(int)
// Derived2::ival: 2
// Derived2::cval: b
//
// Program ended with exit code: 0
