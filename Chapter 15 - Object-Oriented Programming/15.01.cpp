// Exercise 15.01:
/*
 What is a virtual member?
 
 >> "The base class defines as virtual those functions it expects its derived classes to define for themselves" – pg. 592
 
 >> "The base class defines as virtual those functions it expects its derived classes to override. When we call a virtual function through a pointer or reference, the call will be dynamically bound. Depending on the type of the object to which the reference or pointer is bound, the version in the base class or in one of its derived classes will be executed." – pg. 595
 
 >> "A base class specifies that a member function should be dynamically bound by preceding its declaration with the keyword virtual. Any nonstatic member function (§ 7.6, p. 300), other than a constructor, may be virtual. The virtual keyword appears only on the declaration inside the class and may not be used on a function definition that appears outside the class body. A function that is declared as virtual in the base class is implicitly virtual in the derived classes as well. We’ll have more to say about virtual functions in § 15.3 (p. 603)." – pg. 595
*/
