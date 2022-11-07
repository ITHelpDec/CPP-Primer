// Exercise 15.37:
/*
 What changes would your classes need if the derived classes had members of type shared_ptr<Query_base> rather than of type Query?
 
 >> You'd need to change the constructors of the class from which our other class is derived – take OrQuery for example...
*/

// Instead of what we have previously...

OrQuery(const Query &l, const Query &r) : BinaryQuery(l, r, "|")

// ... we would need to change this to accept std::shared_ptr arguments for our lhs and rhs arguments (messy).

OrQuery(std::shared_ptr<Query_base> pl, std::shared_ptr<Query_base> pr) : BinaryQuery(pl, pr, "|")

// it's much cleaner to express the first example, as opposed ot the second
