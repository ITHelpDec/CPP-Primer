// Exercise 12.05:
/*
 We did not make the constructor that takes an initializer_list explicit (§ 7.5.4, p. 296).
 Discuss the pros and cons of this design choice.
*/

StrBlob(std::initializer_list<std::string> il);

StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) { }

// explicit would help ensure that there are no implicit type conversions performed by the compiler

// according to jaege, by not using explicit, we have access to the following benefits
// • we can use = {/*...*/} to initialise a StrBlob object
// • we can use assignment to to assign an initializer_list to a StrBlob object
// • we can pass an initializer_list to funcitons that need a StrBlob parameter
