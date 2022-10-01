// Exercise 11.11:
/*
 Redefine bookstore without using decltype.
*/

multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);

// bool is the desired return value
// the full function expands into the following:
//
// bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
// {
    // return lhs.isbn() < rhs.isbn();
// }
//
// ...so we replicate that using the function arguments...
// ...and by using a pointer to return the value within.
multiset<Sales_data, bool (*)(const Sales_data&, const Sales_data&) > bookstore(compareIsbn);
