// Exercise 9.29:
/*
 Given that vec holds 25 elements, what does vec.resize(100) do?
 What if we next wrote vec.resize(10)?
 
 >> Given that vec.size() = 25, vec.resize(100) will add 75 "0" elements to the current vector, totalling 100 unique elements.
 >> vec.resize(10) will then delete 90 of those elements off the end of the vector, bring vec.size() down to 10.
 */
