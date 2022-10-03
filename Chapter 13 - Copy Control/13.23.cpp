// Exercise 13.22:
/*
 Compare the copy-control members that you wrote for the solutions to the previous section’s exercises to the code presented here.
 Be sure you understand the differences, if any, between your code and ours.
 
 >> Code was okay, but it would be good to see more examples of classes that act like values and classes that act like pointers.
 
 >> e.g. if I change "*ps" to "Hello" after creating 3 identical objects, I would like all 3 instances of "ps" following copy-control operations to say "Hello"
*/

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
