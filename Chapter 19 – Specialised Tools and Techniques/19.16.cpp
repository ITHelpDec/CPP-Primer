// Exercise 19.15:
/*
 Write a type alias that is a synonym for a pointer that can point to the avg_price member of Sales_data.
*/

#include "19.13/Sales_data.hpp"
#include <iostream>

int main()
{
    std::cout << "avg_price(): £" << Sales_data("123-456-789", 5, 120).avg_price() << " pb" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    auto pmf = &Sales_data::avg_price;
    
    Sales_data sd("123-456-780", 5, 125), *sdp = &sd;
    
    std::cout << "avg_price(): £" << (sdp->*pmf)() << " pb" << std::endl;
    
    return 0;
}
