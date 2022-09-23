// Exercise 11.19:
/*
 Define a variable that you initialize by calling begin() on the multiset named bookstore from § 11.2.2 (p. 425).
 Write the variable’s type without using auto or decltype.
*/

#include <set>
#include "Sales_item.h"

int main()
{
    std::multiset<Sales_item, decltype(compareIsbn)*> bookstore(compareIsbn);
    
    // non decltype version taken from earlier exercise
    // iterators in sets are const by default, so ::iterator and ::const_iterator have the same application
    std::multiset<Sales_item, bool (*)(const Sales_item &lhs, const Sales_item &rhs)>::const_iterator bookstore_it = bookstore.begin();

    return 0;
}
