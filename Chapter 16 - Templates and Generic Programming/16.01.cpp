// Exercise 16.01:
/*
 Define instantiation
 
 >> "When we call a function template, the compilter (ordinarily) uses the arguments of the cal lto deduce the template argument(s) for us. That is, when we call compare, the compiler uses the type of the arguments to determine what type to bind to the template parameter T. For example, in this call..."
*/

 std::cout << compare(1, 0) << std::endl;

/*
 "...the arguments have type int. The compiler will deduce int as the template argument and will bind that argument to the template parameter T."
 
 >> "The compiler uses the deduced template parameter(s) to INSTANTIATE a specific version of the function for us. When the compiler instantiates a template, it creates a new "instance" of the template using the actual template argument(s) in place of the corresponding template parameter(s)." – pg. 653
*/
