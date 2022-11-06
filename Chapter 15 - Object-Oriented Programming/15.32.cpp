// Exercise 15.32:
/*
 What happens when an object of type Query is copied, moved, assigned, and destroyed?
 
 >> When copied, all public and private members are copied to the new object; the "using" declaration from Query_base for line_no is also copied across into the new object, and the new object will also have access to the virtual functions from Query_base. Reference count for smart pointers increase accordingly. The same thing applies to copy-assignment.
 
 >> Generally there will be no option to move the contents of this object into the new object, as synthesised move constructors are waived in the presence of a virtual destructor in the base class (unless explictly created) – the same applies to move-assignment operators.
 
 // "As we’ve seen, most base classes define a virtual destructor. As a result, by default, base classes generally do not get synthesized move operations. Moreover, by de- fault, classes derived from a base class that doesn’t have move operations don’t get synthesized move operations either." - pg. 652
 
 >> Destruction is handled in reverse order to construction; first the Query object is destroyed then the Query_base object is destryed. Reference counts fo rthe smart points decrease as appropriate.
*/
