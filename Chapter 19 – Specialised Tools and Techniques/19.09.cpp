// Exercise 19.09:
/*
 Write a program similar to the last one in this section to print the names your compiler uses for common type names.
 If your compiler gives output similar to ours, write a function that will translate those strings to more human-friendly form.
*/

#include <typeinfo>
#include <iostream>

class Base {
    friend bool operator==(const Base&, const Base&);
public:
    // stuff
    int b_ = 42;
protected:
    virtual bool equal(const Base&) const;
};

class Derived : public Base {
public:
    int d_ = 69;
protected:
    bool equal(const Base&) const;
};

// type-sensitive equality operator
bool operator==(const Base &lhs, const Base &rhs)
{
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

// virtual equality operator
bool Derived::equal(const Base &rhs) const
{
    // we already know the types are equal, so the cast should not through
    auto r = dynamic_cast<const Derived&>(rhs);
    
    // return result of Derived member comparators
    // "However, the cast is necessary so that the function can access...
    // ...the derived members of the right-hand operand."
    return d_ == r.d_;
}

bool Base::equal(const Base &rhs) const
{
    return b_ == rhs.b_;
}

int main()
{
    int arr[10];
    Derived d;
    Base *bp = &d;
    
    // std::cout << "42:          " << typeid(42).name() << "\n"
    //           << "arr:         " << typeid(arr).name() << "\n"
    //           << "std::string: " << typeid(std::string).name() << "\n"
    //           << "bp:          " << typeid(bp).name() << "\n"
    //           << "*bp:         " << typeid(*bp).name() << "\n"
    //           << "d:           " << typeid(d).name() << "\n"
    //           << std::endl;
    
    std::cout << "42:          " << (typeid(42) == typeid(int) ? "int" : typeid(42).name()) << "\n"
              << "arr:         " << (typeid(arr) == typeid(int[10]) ? "int[10]" : typeid(arr).name()) << "\n"
              << "std::string: " << (typeid(std::string) == typeid(std::string) ? "std::string" : typeid(std::string).name()) << "\n"
              << "bp:          " << (typeid(bp) == typeid(Base*) ? "Base*" : typeid(bp).name()) << "\n"
              << "*bp:         " << (typeid(*bp) == typeid(Derived) ? "Derived" : typeid(*bp).name()) << "\n"
              << "d:           " << (typeid(d) == typeid(Derived) ? "Derived" : typeid(d).name()) << "\n"
              << std::endl;
    
    return 0;
}

// output with helper function (uncommented)
// 42:          int
// arr:         int[10]
// std::string: std::string
// bp:          Base*
// *bp:         Derived
// d:           Derived
//
// Program ended with exit code: 0

// outout WITHOUT helper function (commented)
// 42:          i
// arr:         A10_i
// std::string: NSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEE
// bp:          P4Base
// *bp:         7Derived
// d:           7Derived
//
// Program ended with exit code: 0
