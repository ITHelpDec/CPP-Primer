// Exercise 19.05:
/*
 When should you use a dynamic_cast instead of a virtual function?
 
 >> "The dynamic_cast operator...safely converts a pointer-to-a-Base-type into a pointer-to-a-Derived-type (or a reference-to-a-Base-type into a reference-to-a-Derived-type) – pg. 825
 
 >> "Ordinarily, we should use virtual functions if we can. When the operation is virtual, the compiler automatically selects the right function according to the dynamic type of the object." – pg. 825
 
 >> "If we cannot use a virtual, we can use one of the RTTI operators (like dynamic_cast)."
 */
