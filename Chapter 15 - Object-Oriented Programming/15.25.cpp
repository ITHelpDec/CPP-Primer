// Exercise 15.25:
/*
 Why did we define a default constructor for Disc_quote?
 What effect, if any, would removing that constructor have on the behavior of Bulk_quote?
 
 >> We defined a default constructor for Disc_quote so that the Bulk_quote could access the constructors in derived class "Disc_quote" and base class "Quote".
 >> If we were to remove that constructor and make it inacessibel then Bulk_quote would not be able to create a construcor, nor access any of the other contructors further up the chain.
 >> This is especially important because we defined a user-defined constructor, so there is no automatically-synthesised default constructor to inherit.
*/
