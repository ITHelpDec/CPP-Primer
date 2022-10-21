// Exercise 14.52:
/*
 Which operator+, if any, is selected for each of the addition expres- sions? List the candidate functions, the viable functions, and the type conversions on the arguments for each viable function:
*/

#include <iostream>

class SmallInt {
    // #1
    friend SmallInt operator+(const SmallInt&, const SmallInt&);
public:
    SmallInt(int = 0) { } // conversion from int
    
    // #2
    operator int() const { return val; } // conversion to int
private:
    std::size_t val;
};

// #1
SmallInt operator+(const SmallInt &lhs, const SmallInt &rhs) { std::cout << "#1: operator+ from SmallInt class" << std::endl; return SmallInt(); }

struct LongDouble {
    LongDouble(double = 0.0) { }
    
    // #3
    // member operator+ for illustration purposes; "+" is usually a non-member
    LongDouble operator+(const SmallInt&) { std::cout << "#3: operator+ from LongDouble struct" << std::endl; return *this; }
    
    // #4
    operator double() { std::cout << "#4: LongDouble::operator double()" << std::endl; }
    // #5
    operator float() { std::cout << "#5: LongDouble::operator float()" << std::endl; }
    
};

// #6
LongDouble operator+(LongDouble&, double) { std::cout << "#6: operator from outside called" << std::endl; return LongDouble(); }

int main()
{
    SmallInt si;
    LongDouble ld;
    
    // (a)
    // ld = si + ld;
    
    // combinations that work:
    // => #2, #4
    // => #2, #5
    // => #2, #4, #5
    // => #2, #4, #6
    // => #2, #3, #4, #6
    // => #2, #3, #5, #6
    // => #2, #4, #5, #6
    // => #1, #2, #3, #4, #6
    // => #1, #2, #3, #5, #6
    
    // basically, as the book states, more than one arithmetic conversion operator() ruins it
    
    // if all enabled?
    // "use of overloaded operator "+" is ambiguous (with operand types 'SmallInt' and 'LongDouble')"
    
    // from: jaege
    //
    // candidate:
    // => all built-in operator+
    // ===> LongDouble::operator+(const SmallInt&)
    // ===> operator+(LongDouble&, double)
    // ===> operator+(const SmallInt&, const SmallInt&)
    //
    // viable:
    // => all built-in operator+
    //
    // best match:
    // => no best match – the below functions were equally good, so ambiguous
    // ===> #4: built-in operator+(int, double)
    // ===> #5: built-in operator+(int, float)
    
    // (b)
    ld = ld + si;
    
    // candidates:
    // => all build-in operator+
    // ===> LongDouble::operator+(const SmallInt&)
    // ===>  operator+(LongDouble&, double)
    // ===>  operator+(const SmallInt&, const SmallInt&)
    //
    // viable:
    // => all build-in operator+
    // ===> LongDouble::operator+(const SmallInt&)
    // ===> operator+(LongDouble&, double)
    //
    // best matched;
    // => #3: LongDouble::operator+(const SmallInt&)
    
}
