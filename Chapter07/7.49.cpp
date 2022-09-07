// Exercise 7.49:
/*
 For each of the three following declarations of combine, explain what
 happens if we call i.combine(s), where i is a Sales_data and s is a string:
 
 (a) Sales_data &combine(Sales_data);
 >> Will compile
 >> "s" will be converted to Sales_data as a temporary object, then fulfil its purpose as a parameter for combine()
 
 (b) Sales_data &combine(Sales_data&);
 >> Will NOT compile
 >> Passing a reference to a temporary object will produce an error
 
 (c) Sales_data &combine(const Sales_data&) const;
 >> Will NOT compile
 >> Similar to above, but should also not be a const member function
 */

