// Exercise 13.09:
/*
 What is a destructor?
 >> "Constructors initialise the nonstatic data members of an object....destructors do whatever work is needed to free the resources used by an object and destroy the nonstatic data members of the object." – pg. 501
 
 What does the synthesized destructor do?
 >> "As with the copy constructor and the copy-assignment operator, for some classes, the synthesized destructor is defined to disallow objects of the type from being destroyed." – pg. 502
 >> "It is important to reliase that the destructor body does not directly destory the members themselves. Members are destory as poart of the implicit desturction phase that follows the destructor body." – pg. 502
 
 When is a destructor synthesized?
 >> The compiler defines a synthesised destructor for any class that does not define its own destuctor". – pg. 502
*/
