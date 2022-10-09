// Exercise 13.45:
/*
 Distinguish between an rvalue reference and an lvalue reference.
 
 .:. RVALUE REFERENCE .:.
 >> "An rvalue reference is a reference that must be bound to an rvalue. An rvalue reference is obtained by using && rather than &" - pg 532
 >> "...whereas an rvalue expression refers to an object's value." – pg 532
 >> "...rvalue references can only be bound to temporaries,.." - pg 533
 >> "Rvalue references refer to objects that are about to be destroyed" - pg 533
 >>
 
 .:. LVALUE REFERENCE .:.
 >> "Generally-speaking, an lvalue expression refers to an object's identity..." –  pg 532
 >> "As we know, we cannot bind regular references – which we'll refer to as lvalue references..."
 >> "Functions that return lvalue references, along with the assignment, subscript, dereferece, and prefix increment / decrement operators, are all examples of expressions that return lvalues. We cannot bind an lvalue reference to these expressions, but we can bind an lvalue reference to const or an rvalue reference to such expressions." - pg 532
*/
