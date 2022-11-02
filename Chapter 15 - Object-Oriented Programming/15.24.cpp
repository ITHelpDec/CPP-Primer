// Exercise 15.24:
/*
 What kinds of classes need a virtual destructor? What operations must a virtual destructor perform?
 
 >> "A virtual destructor is needed if a base pointer pointing to a derived object is deleted"
 
 >> "Like any other virtual, the virtual nature of the destructor is inherited..."
 >> "Thus, classes derived from Quote have virtual destructors, whether they use the synthesized destructor or define their own version..."
 >> "So long as the base class destructor is virtual, when we delete a pointer to base, the correct destructor will be run:"
 
 // "A base class usually needs a virtual destructor to allow objects in the inheritance hierarchy to be dynamically allocated. The virtual destructor must free dynamically alloacted resources in its class if so, otherwise, an empty virtual destructor is enough." - jaege
 
*/
