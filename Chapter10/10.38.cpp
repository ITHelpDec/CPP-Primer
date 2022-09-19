// Exercise 10.38:
/*
 List the five iterator categories and the operations that each supports.
 
 >> (1) Input iterators
 >> (a) equality and inequality operators (==, !=) to compare two iterators
 >> (b) prefix and postfix increment (++iter / iter++) to advance the iterator
 >> (c) de-reference operator (*) to read the actual element located at the iterator; (may only appear at the RIGHT-hand side of an assignment)
 >> (d) the arrow operator (->) as a synonym for (*it).member – this is, de-reference the iterator and fetch a member from the underlying object
 
 >> (2) Output iterators
 >> (a) prefix and postfix increment (++iter / iter++) to advance the iterator
 >> (b) de-reference operator (*), which may only appear at the LEFT-hand side of an assignment)
 
 >> (3) Forward iterators
 >> Forward iterators can support both input and output iterators.
 > They can read or write the same element multiple times
 >> "replace" requires a forward iterator, and iterators on "forward_list" are forward iterators
 
 >> (4) Bi-directional iterators
 >> These iterators can read and write a sequence forwards or backwards
 >> As well as supporting all the operations of a forward iterator, bi-directional iterators also support the prefix and postfix decrement operators (--iter / iter--)
 >> "reverse" requires bi-directional iterators, and bar "forward_list", the library containers supply iterators that meet the requirements for a bi-directional iterator
 
 >> (5) Random-access iterators
 >> These iterators support all the functionality of bi-directional iterators, but they also support the following:
 >> relational operators (<, <=, >, >=)
 >> addition and subtraction operators (+, +=, -, -=)
 >> The subtraction operator (-) when applied to two iterators, which yields the distances between two iterators
 >> The subscript operator (iter[n]) as a synonym for *(iter + n)
 
*/

