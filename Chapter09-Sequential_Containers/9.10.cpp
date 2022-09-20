// Exercise 9.10:
/*
 What are the types of the following four objects?
 
 vector<int> v1;
 const vector<int> v2;
 auto it1 = v1.begin(), it2 = v2.begin();
 auto it3 = v1.cbegin(), it4 = v2.cbegin();
*/
 

it1 = v1.begin();       // std::vector<int>::iterator
it2 = v2.begin();       // std::vector<int>::const_iterator (already const, cannot be ::iterator)
it3 = v1.cbegin();      // std::vector<int>::const_iterator
it4 = v2.cbegin();      // std::vector<int>::const_iterator



