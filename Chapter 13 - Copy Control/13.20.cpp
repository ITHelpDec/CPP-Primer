// Exercise 13.19:
/*
 Explain what happens when we copy, assign, or destroy objects of our TextQuery and QueryResult classes from § 12.3 (p. 484).
 
 >> .:. COPY .:.
 >> members and variables copied (shared_ptr reference count up by 1)
 
 >> .:. ASSIGN .:.
 >> members and variables copied (new shared_ptr reference count up by 1, old reference count down by 1)
 
 >> .:. DESTROY .:.
 >> member sand variables copied (new shaed_ptr reference count down by 1, memory is freed if it reaches 0)
 */

