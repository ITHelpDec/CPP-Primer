// Exercise 15.18:
/*
 Given the classes from page 612 and page 613, and assuming each object has the type specified in the comments, determine which of these assignments are legal.
 Explain why those that are illegal aren’t allowed:
 
 // "User code may use the derived-to-base conversion only if D inherits publicly from B."
// "User code may not use the conversion if D inherits from B using either protected or private."
*/

#include <iostream>

class Base {
    friend class Pal;
public:
    void pub_mem();
    std::size_t size() const { return n; }
protected:
    int prot_mem;
    std::size_t n;
private:
    char priv_mem;
};

class Sneaky : public Base {
    friend void clobber(Sneaky&);
    friend void clobber(Base&);
    int j;
};

struct Pub_Derv : public Base {
    int f() { return prot_mem; }
    
    // 'priv_mem' is a private member of 'Base'
    // char g() { return priv_mem; }
};

struct Priv_Derv : private Base {
    int f1() const { return prot_mem; }
};

struct Prot_Derv : protected Base {
    int f4() const { return prot_mem; }
};

struct Derived_from_Public : public Pub_Derv {
    int use_base() { return prot_mem; }
};

struct Derived_from_Private : public Priv_Derv {
    // 'prot_mem' is a private member of 'Base'
    // int use_base() { return prot_mem; }
    int use_base() { return f1(); }
};

struct Derived_from_Protected : protected Prot_Derv {
    int use_base() { return f4(); }
};

class Pal {
public:
    int f(Base b) { return b.prot_mem; }
    
    // 'j' is a private member of 'Sneaky'
    // int f2(Sneaky s) { return s.j; }
    
    int f3(Sneaky s) { return s.prot_mem; }
};

class D2 : public Pal {
public:
    // 'prot_mem' is a protected member of 'Base'
    // int mem(Base b) { return b.prot_mem; }
    void mem(Base b) { return b.pub_mem(); }
};

class Dervied : private Base {
public:
    using Base::size;
protected:
    using Base::n;
};

void clobber(Sneaky &s) { s.j = s.prot_mem = 0; }

// 'prot_mem' is a protected member of 'Base'
// void clobber(Base &b) { b.prot_mem = 0; }

int main()
{
    Pub_Derv d1;
    Priv_Derv d2;
    d1.pub_mem();
    // 'pub_mem' is a private member of 'Base'
    // d2.pub_mem();
    
    // d1 has type Pub_Derv
    // legal
    Base *p = &d1;
    
    // d2 has type Priv_Derv
    // not legal: "Cannot cast 'Priv_Derv' to its private base class 'Base'"
    // p = &d2;
    
    // d3 has type Prot_Derv
    // not legal: "Cannot cast 'Prot_Derv' to its protected base class 'Base'"
    Prot_Derv d3;
    // p = &d3;
    
    // dd1 has type Derived_from_Public
    // legal
    Derived_from_Public dd1;
    p = &dd1;
    
    // dd2 has type Derived_from_Private
    // not legal: "Cannot cast 'Derived_from_Private' to its private base class 'Base'"
    Derived_from_Private dd2;
    // p = &dd2;
    
    // dd3 has type Derived_from_Protected
    // not legal: "Cannot cast 'Derived_from_Protected' to its protected base class 'Base'"
    Derived_from_Protected dd3;
    // p = &dd3;

    return 0;
}

