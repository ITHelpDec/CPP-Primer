// Exercise 13.22:
/*
 Assume that we want HasPtr to behave like a value.
 That is, each object should have its own copy of the string to which the objects point.
 We’ll show the definitions of the copy-control members in the next section.
 However, you already know everything you need to know to implement these members.
 Write the HasPtr copy constructor and copy-assignment operator before reading on.
*/

// "Classes that behave like values have their own state.
// When we copy a valuelike object, the copy and the original are independent of each other.
// Changes made to the copy have no effect on the original, and vice versa." - pg.510

#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    
    HasPtr (const HasPtr&);
    
    HasPtr &operator=(const HasPtr&);
    
    // destructor operator
    ~HasPtr() { delete ps; }
    
    const std::string get_ps() { return *ps; }
    const int get_i() { return i; }
    void set(const std::string &s) { *ps = s; }
    
private:
    std::string *ps;
    int i;
};

HasPtr::HasPtr(const HasPtr &original) : ps(new std::string(*original.ps)), i(original.i) { }

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    std::string *new_ps = new std::string(*rhs.ps);
    delete ps;
    ps = new_ps;
    i = rhs.i;
    return *this;
}

int main()
{
    std::string s = "manbearpig";
    HasPtr hp1(s);
    HasPtr hp2 = hp1;
    std::cout << "Original valeus:" << std::endl;
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\n" << std::endl;
    
    std::cout << "Setting hp1.*ps to a different word..." << std::endl;
    hp1.set("totally");
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\n" << std::endl;
    
    std::cout << "Setting hp2.*ps to a different word..." << std::endl;
    hp2.set("cereal");
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\n" << std::endl;
    
    return 0;
}
