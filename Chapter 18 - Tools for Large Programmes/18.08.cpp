// Exercise 18.08:
/*
 Review the classes you’ve written and add appropriate exception spec- ifications to their constructors and destructors.
 If you think one of your destructors might throw, change the code so that it cannot throw.
 
 // So many terrible questions in this chapter...
 
 // Remember to noexcept with move constructor and move-assignment oeprators
 
*/

class Base {
public:
    Base() = default;
    
    ~Base() noexcept;
    
    virtual double f1(double) noexcept;     // cannot throw
    virtual int f2() noexcept(false);       // can throw
    virtual void f3();                      // can throw
};

class Derived : public Base {
    // "Exception specification of overriding function is more lax than base version"
    // basically, "doesn't have noexcept – needs noexcept
    // double f1(double);
    
    int f2() noexcept(false);               // okay: same as base
    void f3() noexcept;                     // okay; derived f3() is more restrictive
};
