// Exercise 16.67:
/*
 Would defining these specializations affect function matching for debug_rep?
 If so, how?
 If not, why not?
 
 >> No – the non-template version is more specialised and will be chosen over the specialisation (see below).
 
 // "Both function templates are viable and provide an equally good (i.e., exact) match to the call. However, the version with character array parameters is more specialised (§ 16.3, p. 695) and is chosen for this call." – pg. 708
 
*/
