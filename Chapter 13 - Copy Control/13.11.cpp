// Exercise 13.11:
/*
 Add a destructor to your HasPtr class from the previous exercises.
*/

#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    
    HasPtr (const HasPtr&);
    
    HasPtr &operator=(const HasPtr&);
    
    // destructor operator
    ~HasPtr();
    
    const std::string get_ps() { return *ps; }
    const int get_i() { return i; }
    
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
    
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"" << std::endl;
    
    return 0;
}
