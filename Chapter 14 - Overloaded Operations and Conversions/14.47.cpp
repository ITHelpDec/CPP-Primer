// Exercise 14.47:
/*
 Explain the difference between these two conversion operators:
*/

struct Integral {
    operator const int(); // (a)
    operator int() const; // (b)
};

// both compiled fine on Sales_data class, but not explicit

// (a) will convert Integral to "const int", but may change the object on which it is acting
// (b) will convert Integral to "int", but will not change the object on which it is acting
