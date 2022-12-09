// Exercise 16.25:
/*
 Explain the meaning of these declarations:
*/

#include <string>
#include "Sales_data"

// "Under the new standard, we can avoid this overhead through an explicit instantiation. An explicit instantiation has the form: " – pg. 675

extern template class vector<std::string>;  // explicit declaration

// In the explicit instantiation, the compiler will not generate code for that instantiation in that file.
// "Defining an instantiation as extern is a promise that there will be a nonextern use of that instantiation elsewhere in the programme." – pg. 675

template class vector<Sales_data>;

// In this example, the compiler WILL generate code for the above instantiation in its file – it will instantiate all members of the template "vector".
