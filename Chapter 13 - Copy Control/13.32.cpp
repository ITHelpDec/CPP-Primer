// Exercise 13.32:
/*
 Would the pointer-like version of HasPtr benefit from defining a swap function?
 If so, what is the benefit?
 If not, why not?
 
 >> I imagine there would be a performance benefit from defining a swap function for the pointer-like version of HasPtr.
 >> In terms of raw bytes, a pointer is typically smaller than a string, so swapping pointers over a swapping strings would be a less expensive operation.
*/
