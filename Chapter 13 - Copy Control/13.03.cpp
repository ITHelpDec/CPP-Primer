// Exercise 13.03:
/*
 What happens when we copy a StrBlob? What about StrBlobPtrs?
 
 >> If we make a copy of StrBlob, we will copy all of the members and variables within the StrBlob class.
 >> We must, however, be mindful of the shared_ptr increasing its reference count and pointing to the exact same string vector ("data") – this isn't technically a "copy" of the data; moreso, another instance of a reference to the same memory location, which may either be exactly what we want (or exactly what we don't want).
 
 >> Same thing applies to StrBlobPtr
*/
