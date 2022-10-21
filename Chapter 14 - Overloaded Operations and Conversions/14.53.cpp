// Exercise 14.53:
/*
 Given the definition of SmallInt on page 588, determine whether the following addition expression is legal.
 If so, what addition operator is used?
 If not, how might you change the code to make it legal?
*/

#include <iostream>

class SmallInt {
    friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int = 0) { }
    
    operator int() const { }
    operator double() const { }
private:
    std::size_t val;
};

SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs) { }

int main() {
    SmallInt s1;
    
    // illegal: ambiguous call as is
    // double d = s1 + 3.14;
    
    // .:. workarounds .:.
    // (1) static_cast<double> works, but is a sign of poor design
    // (2) double d = s1 + SmallInt(3.14);, but this gives funky answers
    // (3)
    //      (a) replace...  operator int() const
    //      (b) ...with...  operator double() const
    //      (c) ...and...   remove friend operator+() functions
    
    return 0;
}
