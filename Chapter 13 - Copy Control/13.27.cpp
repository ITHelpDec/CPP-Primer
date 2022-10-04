// Exercise 13.27:
/*
 Define your own reference-counted version of HasPtr.
*/

#include <string>
#include <iostream>

class HasPtr {
public:
    // new default constructor (including a pointer to "use" member)
    // HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    
    HasPtr(const HasPtr&);
    
    HasPtr &operator=(const HasPtr&);
    
    ~HasPtr();
    
    const std::string get_ps() { return *ps; }
    const int get_i() { return i; }
    void set(const std::string &s) { *ps = s; }
    std::size_t get_use() { return *use; }
    
private:
    std::string *ps;
    int i;
    
    // new member to keep track of how many objects share "*ps"
    std::size_t *use;
};


// copy constructor
// not pointing to underlying values this time round, so no need for using "new"
// HasPtr::HasPtr(const HasPtr &original) : ps(new std::string(*original.ps)), i(original.i) { }
HasPtr::HasPtr(const HasPtr &original) : ps(original.ps), i(original.i), use(original.use) { ++*use; }

// destructor
HasPtr::~HasPtr()
{
    // if the reference count goes to zero
    if (--*use == 0) {
        // delete the string and delete the counter
        delete ps;
        delete use;
    }
    std::cout << "~ (use count = " << *use << ")" << std::endl;
}

// copy-assginment oeprator
// "The copy-assignment operator, as usual, does the work common to the copy constructor and to the destructor.
// That is, the assignment operator must incremenet the counter of the right-hand operand (i.e. the work of the copy constructor) and decrement the counter of hte left-hand operand, deleting the memory used if appropriate (i.e. the work of the destructor)" – pg. 515
HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    // increment the use count of the right-hand operand
    ++*rhs.use;
    
    // decrement the use count of the left-hand operand
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    
    // copy data from rhs into this object
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    
    return *this;
}

int main()
{
    std::string s = "manbearpig";
    HasPtr hp1(s);
    HasPtr hp2 = hp1;
    
    HasPtr hp3(s);
    hp3 = hp1;
    
    std::cout << "Original valeus:" << std::endl;
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\nhp3.ps\t= \"" << hp3.get_ps() << "\"" << std::endl;
    std::cout << "Use count: hp1 = " << hp1.get_use() << ", hp2 = " << hp2.get_use() << ", hp3 = " << hp3.get_use() << "\n" << std::endl;
    
    std::cout << "Setting hp1.*ps to a different word..." << std::endl;
    hp1.set("totally");
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\nhp3.ps\t= \"" << hp3.get_ps() << "\"" << std::endl;
    std::cout << "Use count: hp1 = " << hp1.get_use() << ", hp2 = " << hp2.get_use() << ", hp3 = " << hp3.get_use() << "\n" << std::endl;
    
    std::cout << "Setting hp2.*ps to a another word..." << std::endl;
    hp2.set("cereal");
    std::cout << "s\t\t= \"" << s << "\"\nhp1.ps\t= \"" << hp1.get_ps() << "\"\nhp2.ps\t= \"" << hp2.get_ps() << "\"\nhp3.ps\t= \"" << hp3.get_ps() << "\"" << std::endl;
    std::cout << "Use count: hp1 = " << hp1.get_use() << ", hp2 = " << hp2.get_use() << ", hp3 = " << hp3.get_use() << "\n" << std::endl;
    
    std::cout << "Destroying objects:" << std::endl;
    
    return 0;
}
