// Exercise 9.37:
/*
 Why don’t list or array have a capacity member?

 >> arrays have a fixed size from initialisation so it's size and initialisation would be the same.
 
 >> lists do not support random access (each element is stored separately in memory); there is also no need to reallocate elements, meaning pre-allocation of memory is unnecessary.
*/
