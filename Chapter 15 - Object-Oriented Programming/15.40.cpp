// Exercise 15.40:
/*
 In the OrQuery eval function what would happen if its rhs member returned an empty set?
 What if its lhs member did so?
 What if both rhs and lhs returned empty sets?
 
 >> ret_lines starts with using lhs; it lhs is empty, then an empty set will be created
 >> if rhs is empty, then the ret_lines->insert() member function will insert nothing
 >> if rhs AND lhs are empty then we will be left with an empty set
 
*/
