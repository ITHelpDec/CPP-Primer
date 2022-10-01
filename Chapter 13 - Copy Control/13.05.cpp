// Exercise 13.05:
/*
 Assuming Point is a class type with a public copy constructor, identify each use of the copy constructor in this program fragment:
*/

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : pa(new std::string(s)), i(0) { }
    
    // copy constructor
    HasPtr (const HasPtr&);
private:
    std::string *pa;
    int i;
};

// explicit declaration
HasPtr::HasPtr(const HasPtr &original) : pa(new std::string(*original.pa)), i(original.i) { }

// (1) declaration
// HasPtr(const HasPtr &original)

// (2) to copy, we want the original "pa" and "i"
// pa(new std::string(s)
// ...becomes..
// pa(new std::string(*original.pa);
// ...and...
// i(0)
// ...becomes...
// i(original.i)
