// Exercise 16.66:
/*
 What are the advantages and disadvantages of overloading these debug_rep functions as compared to defining specializations?
*/

// Function Overloading versus Template Specialisations

// "Whether we define a particular function as a specialization or as an indepen- dent, nontemplate function can impact function matching. For example, we have defined two versions of our compare function template, one that takes references to array parameters and the other that takes const T&. The fact that we also have a specialization for character pointers has no impact on function matching. When we call compare on a string literal:"

compare("hi", "mom")

// "Both function templates are viable and provide an equally good (i.e., exact) match to the call. However, the version with character array parameters is more special- ized (§ 16.3, p. 695) and is chosen for this call." – pg. 708
