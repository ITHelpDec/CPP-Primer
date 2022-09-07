// Exercise 7.46
/*
 Which, if any, of the following statements are untrue?
 Why?
 
 (a) A class must provide at least one constructor.
 >> True
 >> If a constructor isn't provided by the programmer, then the compiler will provide a default constructor
 
 (b) A default constructor is a constructor with an empty parameter list.
 >> Untrue
 >> The parameter list is full, but they will be uninitialised
 
 (c) If there are no meaningful default values for a class, the class should not provide a default constructor.
 >> True?
 
 (d) If a class does not define a default constructor,the compiler generates one that
 initializes each data member to the default value of its associated type.
 >> Untrue
 >> This would only hold true if no constructors were defined, rather than just the default constructor
 */

