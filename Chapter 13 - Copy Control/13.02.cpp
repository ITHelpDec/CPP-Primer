// Exercise 13.02:
/*
 Explain why the following declaration is illegal:
 
 Sales_data::Sales_data(Sales_data rhs);
 
 >> A copy constructor must refer to a const reference, otherwise it will end up in an infinite loop.
 
 "If that parameter were not a reference, then the call would never succeed – to call the copy constructor, we'd need to use the copy constructor to copy the argument, but to copy the argument, we'd need to call the copy constcutor, and so on indefinitely." – pg. 498
 
 Sales_data::Sales_data(const Sales_data &rhs);
*/
