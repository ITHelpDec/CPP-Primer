// Exercise 9.21:
/*
 Explain how the loop from page 345 that used the return from insert to add elements to a list would work if we inserted into a vector instead.
 
 list<string> lst;
 auto iter = lst.begin();
 while (cin >> word)
     iter = lst.insert(iter, word); // same as calling push_front
 
 >> If the above code is applied to vectors, the end result will be the same.
 >> Insertion at the beginning of a list is not an expensive action – the same cannot be said for vectors.
*/


