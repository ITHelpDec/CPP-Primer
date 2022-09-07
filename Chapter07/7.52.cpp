// Exercise 7.52:
/*
 Using our first version of Sales_data from § 2.6.1 (p. 72), explain the
 following initialization.
 Identify and fix any problems.
 
 Sales_data item = {"978-0590353403", 25, 15.99};
 
 should it not be
 
 Sales_data item("978-0590353403", 25, 15.99);
 
 ?
 */

#include <string>

// aggregate class listed below
// (1) struct defaults all members to public
// (2) no constructors are defined
// (3) it has no in-class initialisers
// (4) it has no base classes or virtual functions

struct Sales_data {
    std::string bookNo;     // = "";
    unsigned units_sold;    //= 0;
    double revenue;         //= 0.0;
};

int main() {
    // Parameters appear in the same order as the struct members...no issue compiling
    Sales_data item = {"978-0590353403", 25, 15.99};

    // The following would produce an error because the parameters do not match the order of member declaration
    // Sales_data item = {25, "978-0590353403", 15.99};
    
    return 0;
}
