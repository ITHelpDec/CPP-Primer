// Example 16.08:
/*
 In the “Key Concept” box on page 108, we noted that as a matter of habit C++ programmers prefer using != to using <.
 Explain the rationale for this habit.
 
 >> I imagine this is because not all structures have a "<" operator, whereas they do have "==" or "!=".
 
 >> "C++ programmers use != as a matter of habit. They do so for the same reason that they use iterators rather than subscripts. This coding style appleis equally well to various kinds of containers provided by the library."
 
 >> "As we've seen, only a few library types, std::vector and std::string being among them, have the subscript operator. Similarly, all of the library containers have iterators that define the == nad != operators. Most of the iterators do not have hte "<" operator. By routinely using iterators and !=, we don't have to worry about the precise type of container we're processing." – pg. 108
*/
