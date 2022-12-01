// Exercise 16.03:
/*
 Call your compare function on two Sales_data objects to see how your compiler handles errors during instantiation.
*/

#include "Sales_data.h"
#include <iostream>
#include <functional>

template <typename T> T compare(const T &sd1, const T &sd2) {
    if (std::less<T>()(sd1, sd2)) { return -1; }
    if (std::less<T>()(sd2, sd1)) { return 1; }
    return 0;
}

int main()
{
    // No matching constructor for initialization of 'Sales_data'
    Sales_data sd1 = { "001", 20, 4 }, sd2 = { "002", 25, 5 };
    
    // this does not work
    // std::cout << compare(sd1, sd2) << std::endl;
    
    // does not work with string comparison
    // std::cout << compare(sd1.bookNo, sd2.bookNo) << std::endl;
    
    // double comparison fine
    std::cout << compare(sd1.revenue, sd2.revenue) << std::endl;
    
    // int comparison fine
    std::cout << compare(sd1.units_sold, sd2.units_sold) << std::endl;
    
    return 0;
}
