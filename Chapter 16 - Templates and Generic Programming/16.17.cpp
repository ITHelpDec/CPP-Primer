// Exercise 16.17:
/*
 What, if any, are the differences between a type parameter that is declared as a typename and one that is declared as a class?
 When must typename be used?
 
 >> Under normal circumstances, there are no differences between a type parameter that is declared as a typename and one that is declared as a class.
 
 The one time we must use typename is when we want to use the type member of a template type parameter.
 
 >> "As a result, if we want to use the type member of a template type parameter, we must explicitly tell the compiler that the name is a type. We do so by using the keyword typename." – pg 670
 
 >> ...in combination with the scope operator (::)
*/
