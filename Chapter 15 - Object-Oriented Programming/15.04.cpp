// Exercise 15.04:
/*
 Which of the following declarations, if any, are incorrect?
 Explain why.
*/

class Base { ... };

// (a) error: can't derive a  class from itself
class Derived : public Derived { ... };

// (b) definition, not declaration
// ok, but will only give access to private members?
class Derived : private Base { ... };

//(c) error: declaration incorrect, don't need to list base class
// should just be class Derived;
class Derived : public Base;
