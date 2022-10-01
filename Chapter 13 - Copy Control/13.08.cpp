// Exercise 13.08:
/*
 Write the assignment operator for the HasPtr class from exercise 13.5 in § 13.1.1 (p. 499).
 As with the copy constructor, your assignment operator should copy the object to which ps points.
*/

#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    
    // copy constructor
    HasPtr (const HasPtr&);
    
    // copy-assignment constructor
    HasPtr &operator=(const HasPtr&);
    
    // create functions to return private variables
    const std::string get_ps() { return *ps; }
    const int get_i() { return i; }
    
private:
    std::string *ps;
    int i;
};

// explicit declaration
// dynamically allocate "new string" to the object to which "ps" points
HasPtr::HasPtr(const HasPtr &original) : ps(new std::string(*original.ps)), i(original.i) { }

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    // terrible exercise
    // used source code from website and other answers to complete
    
    // (1) copy the underlying string
    std::string *new_ps = new std::string(*rhs.ps);
    // (2) free the old memory
    delete ps;
    // (3) copy data from rhs into this object
    ps = new_ps;
    i = rhs.i;
    return *this;
}

int main()
{
    std::string s = "manbearpig";
    HasPtr hp1(s);
    HasPtr hp2 = hp1;
    
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"" << std::endl;
    
    return 0;
}
