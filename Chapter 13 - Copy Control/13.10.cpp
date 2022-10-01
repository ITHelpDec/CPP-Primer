// Exercise 13.10:
/*
 What happens when a StrBlob object is destroyed? What about a StrBlobPtr?
 
 >> If StrBlob is destroyed, all its members and variables are destroyed.
 >> An instance of the shared_ptr will be destoryed, but it will continue to exist until the rederence count is 0.
 
 >> In StrBlobPtr, we have used a weak_ptr – this reference decrement has no bearing on our vector like a shared_ptr would.
*/
