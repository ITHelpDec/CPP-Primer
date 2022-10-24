// Exercise 15.19:
/*
 Assume that each of the classes from page 612 and page 613 has a member function of the form:
 
 // void memfcn(Base &b) { b = *this; }
 
 For each class, determine whether this function would be legal.
*/

#include <iostream>

class Base {
    friend class Pal;
public:
    void pub_mem();
    std::size_t size() const { return n; }
    
    void memfcn(Base &b) { b = *this; }
protected:
    int prot_mem;
    std::size_t n;
private:
    char priv_mem;
};

struct Pub_Derv : public Base { void memfcn(Base &b) { b = *this; } };

struct Priv_Derv : private Base { void memfcn(Base &b) { b = *this; } };

struct Prot_Derv : protected Base { void memfcn(Base &b) { b = *this; } };

struct Derived_from_Public : public Pub_Derv { void memfcn(Base &b) { b = *this; } };

struct Derived_from_Private : public Priv_Derv {
    // 'Base' is a private member of 'Base'
    // void memfcn(Base &b) { b = *this; }
};

struct Derived_from_Protected : protected Prot_Derv { void memfcn(Base &b) { b = *this; } };

int main()
{
    Base b;
    
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;
    
    d1.memfcn(b);           // legal, although aurocorrects to "d1.Base::memfcn(b);" in IDE
    d2.memfcn(b);           // legal
    d3.memfcn(b);           // legal
    
    dd1.memfcn(b);          // legal
    dd2.memfcn(b);          // not legal: 'Base' is a private member of 'Base'
    dd3.memfcn(b);          // legal
    
    return 0;
}
