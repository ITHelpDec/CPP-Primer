// Exercise 19.13:
/*
 Define the type that can represent a pointer to the bookNo member of the Sales_data class.
*/

#include "Sales_data.hpp"

int main()
{
    // again...........private member....
    // set a friend operator or define new function with class
    
    // would be able to call the following if the member were public
    
    // Sales_data().Sales_data::*bnptr = &Sales_data::bookNo;
    
    // can create the following function inside our class header
    
    // static const std::string Sales_Data::*isbnPtr()
    // {
    //     return &Sales_data::bookNo;
    // }
    //
    
    std::cout << "bookNo: " << Sales_data("convolutedAF").*Sales_data::isbnPtr() << std::endl;
    
    return 0;
}
