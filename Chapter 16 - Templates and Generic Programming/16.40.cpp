// Exercise 16.40:
/*
 Is the following function legal?
 If not, why not?
 If it is legal, what, if any, are the restrictions on the argument type(s) that can be passed, and what is the return type?
*/

#include <vector>
#include <iostream>
#include "Blob.hpp"
#include <string>

template <typename It> auto fcn3(It beg, It end) -> decltype(*beg + 0)
{ return *beg; }

template <typename It> auto fcn(It beg, It end) -> decltype(beg)
{ return beg; }

int main()
{
    std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    Blob<std::string> sblob = { "man", "bear", "pig" };
    
    // "Non-const lvalue reference to type 'int' cannot bind to a temporary of type 'decltype(* beg + 0)' (aka 'int')"
    // auto &i = fcn3(ivec.begin(), ivec.end());
    
    // without the reference operator, the code with run
    auto i3 = fcn3(ivec.begin(), ivec.end());
    
    // the above amendment will not work for our custom Blob<T> class
    // auto s3 = fcn3(sblob.begin(), sblob.end());
    
    // the following code was used to build begin() and end() members in "Blob.hpp"
    // typename std::vector<T>::iterator begin() { return data->begin(); }
    // typename std::vector<T>::iterator end() { return data->end(); }
    
    std::cout << "i3: " << i3 << std::endl;
    
    // instead, we could call something like fcn() from the earlier exercises...
    // ...using iterators and dereferencing the elements
    auto i = fcn(ivec.begin(), ivec.end());
    auto s = fcn(sblob.begin(), sblob.end());
    
    std::cout << "i: " << *i << std::endl;
    std::cout << "s: " << *s << std::endl;
    
    return 0;
}
