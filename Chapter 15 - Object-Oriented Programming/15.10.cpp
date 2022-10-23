// Exercise 15.10:
/*
 Recalling the discussion from § 8.1 (p. 311), explain how the program on page 317 that passed an ifstream to the Sales_data read function works.
 
 // "As we noted in § 8.1 (p. 311), we can use an object of an inherited type in places where an object of the original type is expected. This fact means that functions that are written to take a reference (or pointer) to one of the iostream types can be called on behalf of the corresponding fstream (or sstream) type. That is, if we have a function that takes an ostream&, we can call that function passing it an ofstream object, and similarly for istream& and ifstream." – pg. 317.
 
 // "The library lets us ignore the differences among these different kinds of streams by using inheritance. As with templates (§ 3.3, p. 96), we can use classes related by inheritance without understanding the details of how inheritance works. We’ll cover how C++ supports inheritance in Chapter 15 and in § 18.3 (p. 802)." – pg. 311
  
 // "Briefly, inheritance lets us say that a particular class inherits from another class. Ordinarily, we can use an object of an inherited class as if it were an object of the same type as the class from which it inherits." – pg. 311
 
 >> .:. TL;DR .:.
 >> std::ifstream is inherited from std::istream
 >> In "read(input, total)", input is of derived type
 >> This calls the std::istream function specific to std::ifstream
*/

