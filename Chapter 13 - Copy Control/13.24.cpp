// Exercise 13.24:
/*
 What would happen if the version of HasPtr in this section didn’t define a destructor?
 >> Without the destructor we would not free the dynamically allocated memory for our string pointer, which woudl lead to a memory leak.
 
 What if HasPtr didn’t define the copy constructor?
 >> If we didn't define the copy constructor, then both the new object and the old object would point to the same underlying string instead of creating its own.
*/
