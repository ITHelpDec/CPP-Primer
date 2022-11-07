// Exercise 15.38:
/*
 Are the following declarations legal?
 If not, why not?
 If so, explain what the declarations mean.
 
 // BinaryQuery a = Query("fiery") & Query("bird");
 // AndQuery b = Query("fiery") & Query("bird");
 // OrQuery c = Query("fiery") & Query("bird");
 
 All declarations are illegal – BinaryQuery is an abstract base class; the others are private conrete classes and only exist when called into action by their corresponding operators ("&" or "|")
*/
