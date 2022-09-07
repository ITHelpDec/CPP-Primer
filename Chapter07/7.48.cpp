// Exercise 7.48:
/*
 Assuming the Sales_data constructors are not explicit, what operations happen during the following definitions
 
 (a) string null_isbn("9-999-99999-9");
 >> This will call the string constructor from null_isbn
 
 (b) Sales_data item1(null_isbn);
 >> This will call the Sales_data constructor
 
 (c) Sales_data item2("9-999-99999-9");
 >> This will first convert "9-999-99999-9" to a string, then call the Sales_data constructor
 
 What happens if the Sales_data constructors are explicit?
 >> No difference
 */

