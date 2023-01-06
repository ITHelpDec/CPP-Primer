// Exercise 19.11:
/*
 What is the difference between an ordinary data pointer and a pointer to a data member?
 
 >> "Unlike ordinary pointers, a pointer to member also incorporates the class that contains the member."
 >> "Hence, we must precede the * with classname:: to indicate that the pointer we are defining can point to a member of classname." – pg. 836
 
 // e.g.
 // const std::string Screen::*pdata;
                         ^    ^  ^
                         ^    ^  ^
                         ^    ^  pointer-to-data-member
                         ^    ^
                         ^    dereference operator
                         ^
                         classname::
*/
