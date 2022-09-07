// Exercise 7.47:
/*
 Explain whether the Sales_data constructor that takes a string should be explicit.
 What are the benefits of making the constructor explicit?
 What are the drawbacks?
 
 Sales_data item1(null_book);
 
 The consensus is it should be explicit
 
 Defining an explicit constructor will stop the compiler from converting the object from the type you're expecting to the type that's defined by the class
 
 One drawback might be that explicit constructors can only be used for direct initialisation?
 */

