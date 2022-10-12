// Exercise 14.01:
/*
 In what ways does an overloaded operator differ from a built-in operator?
 In what ways are overloaded operators the same as the built-in operators?
 
 >> .:. DIFFERENCES .:.
 >> "An overloaded operator can be called directly as a normal function, whereas a built-in operator cannot."
 >> "Overloaded operators do not preserve order of evaluation, and/or potentially short-circuit the evaluation"
 >> "An overloaded operator function must either be a member of a class or have at least one parameter of class type [this]."
 >> "Only part of the existing operators can be overloaded (we cannot invent new operator symbols)."
 
 >> .:. SIMILARITIES .:.
 >> "Like any other function, an overloaded operator has a return type, a parameter list, and a body" - pg 552
 >> "An overloaded operator has the same precedence and associativity (§ 4.1.2, p. 136) as the corresponding built-in operator." - pg 553
*/
