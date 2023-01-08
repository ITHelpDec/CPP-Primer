// Exercise 19.19:
/*
 Write a function that takes a vector<Sales_data>...
 ...and finds the first element whose average price is greater than some given amount.
*/

#include <vector>
#include "Sales_data.hpp"

int main()
{
    std::vector<Sales_data> sdvec = {
        Sales_data("a", 5, 120),
        Sales_data("b", 5, 125),
        Sales_data("c", 5, 130),
        Sales_data("d", 5, 135),
        Sales_data("e", 5, 140)
    };
    
    double d = 25.00;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using a lambda function...\n";
    std::cout << "First book with greater-than-average price of £" << d << "...\n>>> book \"";
    std::cout << std::find_if(sdvec.begin(), sdvec.end(),
                              [&d] (const Sales_data &sd) { return sd.avg_price() > d; } )->isbn()
    << "\"\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::function<>()...\n";
    
    // y tho?
    std::function<double (const Sales_data&)> fcn = &Sales_data::avg_price;
    
    std::cout << "First book with greater-than-average price of £" << d << "...\n>>> book \"";
    std::cout << std::find_if(sdvec.begin(), sdvec.end(),
                              [&d, &fcn] (const Sales_data &sd) { return fcn(sd) > d; } )->isbn()
    << "\"\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::mem_fn...\n";
    std::cout << "First book with greater-than-average price of £" << d << "...\n>>> book \"";
    std::cout << std::find_if(sdvec.begin(), sdvec.end(),
                              [&d] (const Sales_data &sd) { return std::mem_fn(&Sales_data::avg_price)(sd) > d; } )->isbn()
    << "\"\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::bind...\n";
    std::cout << "First book with greater-than-average price of £" << d << "...\n>>> book \"";
    std::cout << std::find_if(sdvec.begin(), sdvec.end(), [&d] (const Sales_data &sd)
                              { return std::bind(&Sales_data::avg_price, std::placeholders::_1)(sd) > d; } )->isbn()
    << "\"\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}

// output:
// Using a lambda function...
// First book with greater-than-average price of £25...
// >>> book "c"
//
// Using std::function<>()...
// First book with greater-than-average price of £25...
// >>> book "c"
//
// Using std::mem_fn...
// First book with greater-than-average price of £25...
// >>> book "c"
//
// Using std::bind...
// First book with greater-than-average price of £25...
// >>> book "c"
//
// Program ended with exit code: 0
