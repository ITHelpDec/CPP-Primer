// Exercise 14.11:
/*
 What, if anything, is wrong with the following Sales_data input operator?
 What would happen if we gave this operator the data in the previous exercise?
 
 >> The input would be "valid", but example (b) would produce 24 * 0.95 as our revenue (not what we want)
*/

//
// std::istream& operator>>(std::istream &in, Sales_data &s)
// {
//     double price;
//     in >> s.bookNo >> s.units_sold >> price;
//     s.revenue = s.units_sold * price;
//     return in;
// }
//
