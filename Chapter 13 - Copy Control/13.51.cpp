// Exercise 13.51:
/*
 Although unique_ptrs cannot be copied, in § 12.1.5 (p. 471) we wrote a clone function that returned a unique_ptr by value.
 Explain why that function is legal and how it works.
 
 // "There is one exception to the rule that we cannot copy a std::unique_ptr.
 // We can copy or assign a std::unique_ptr that is about to be destroyed.
 // The most common example is when we returna std::unique_ptr from a function." - pg 471
 
*/

#include <memory>

std::unique_ptr<int> clone(int p) {
    return std::unique_ptr<int>(new int(p));
}

std::unique_ptr<int> clone_ret(int p) {
    std::unique_ptr<int> ret(new int(p));
    return ret;
}

/*
 // "In both cases, the compiler knows that the object being returned is about to be destoryed.
 // In such cases, the compiler does a special kind of 'copy'..." - pg 471
 
 // "copy ellision"?"
 //
 // std::unique_ptr does not have a "copy constructor" - when a class does not define a copy constructor the move constructor will be used instead.
 //
 // Because the return from these function is an rvalue, the move constructor / move-assignment operator will be called
 
 // We also do not need to worry about destruction or deallocation because the std::unique_ptr is about to be destroyed.
 */
