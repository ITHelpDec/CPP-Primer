// Exercise 13.07:
/*
 What happens when we assign one StrBlob to another?
 What about StrBlobPtrs?
 
 >> This feels like a similar question to 13.2?
 
 >> StrBlob: we would copy the initializer list "data" and the memory location of the shared_ptr (all the members and variables, essentially)
 >> StrBlobPtr: we get a copy of the StrBlob it points to, similar story with members and functions etc.
*/
