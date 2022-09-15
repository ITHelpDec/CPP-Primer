// Exercise 10.07:
/*
 We said that algorithms do not change the size of the containers over which they operate.
 Why doesn’t the use of back_inserter invalidate this claim?
 
 >> std::back_inserter is not an algorithm – it creates an iterator to use as the destination for the algorithm
*/
