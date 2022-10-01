// Exercise 11.10:
/*
 Could we define a map from vector<int>::iterator to int?
 What about from list<int>::iterator to int? I
 n each case, if not, why not?
*/

#include <map>
#include <vector>
#include <list>

// We are allowed to perform the following because std::vector iteraotrs support iterator arithmetic as well as relational operators such as "<", which are necessary when comparing keys in an ordered container
std::map<std::vector<int>::iterator, int>

// std::list, however, supports neither iterator arithmetic nor relational operators, so would not work in an ordered map
std::map<std::vector<int>::iterator, int>
