// Exercise 7.41
/*
 Assume we have a class named NoDefault that has a constructor that takes an int, but has no default constructor.
 Define a class C that has a member of type NoDefault.
 Define the default constructor for C.
 */

class NoDefault {
public:
    NoDefault(int i) : x(i) {}  // default takes an int
private:
    int x;  // int declared in private
};

class C {
public:
    C() : member(0) {}  // constructor defined with member defaulted to 0
private:
    // member (not member function) created of type NoDefault
    // think like "int member", which would be a member of type int
    NoDefault member;
};
