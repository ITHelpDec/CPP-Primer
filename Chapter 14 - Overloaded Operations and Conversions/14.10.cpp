// Exercise 14.10:
/*
 Describe the behavior of the Sales_data input operator if given the following input:
 
 // (a) 0-201-99999-9 10 24.95
 >> no issues
 
 // (b) 10 24.95 0-210-99999-9
 >> std::istream is valid, but not ideal.
 >> bookNo will be read as "10"
 >> units_sold will be read as 24 (converted to unsigned from 24.95"
 >> 0.95 will be read into revenue as it is expecting a double
 
*/
