// Exercise 14.03:
/*
Both string and vector define an overloaded == that can be used to compare objects of those types.
 Assuming svec1 and svec2 are vectors that hold strings, identify which version of == is applied in each of the following expressions:
 
 // (a) "cobble" == "stone" => built-in version (not overloaded)
 
 // (b) svec1[0] == svec2[0] => string version (subscript is rvalue)
 
 // (c) svec1 == svec2 => vector version
 
 // (d) svec1[0] == "stone"" => string version
 
*/
