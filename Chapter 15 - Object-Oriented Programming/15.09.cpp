// Exercise 15.09:
/*
 When is it possible for an expression’s static type to differ from its dynamic type?
 Give three examples in which the static and dynamic type differ.
 
 >> "It is crucial to understand that the static type of a pointer or reference to a base class may differ from its dynamic type." – pg. 602
 
 // "A pointer or reference to a base-class type can refer to an object of derived type. In such cases the static type is a reference (or pointer) to the base, but the dynamic type is a reference (or pointer) to the derived"
 
 // "Classes related by inheritance are an important exception: We can bind a pointer or reference to a base-class type to an object of a type derived from that base class. For example, we can use a Quote& to refer to a Bulk_quote object, and we can assign the address of a Bulk_quote object to a Quote*." – pg. 601
*/

class Base { };
class Derived : public Base { };

Base b;
Derived d;

// (1) *Base = &Derived
Base *bp = &d;

// (2) &Base = Derived
Base &b_ref = d;

// (3) *Base = DerivedPointer
Derived *dp = &d;
Base *bp2 = dp
