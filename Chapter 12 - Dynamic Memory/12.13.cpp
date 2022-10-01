// Exercise 12.13:
/*
 What happens if we execute the following code?
*/

/* Output:
 Using x (5) as test variables.
 
 p: (0x1005498a8), *p: (5), &p: (0x7ffeefbff290)
 sp: (0x1005498a8), *sp: (5), &sp: (0x7ffeefbff280)
 sp has 1 occurence.

 p: (0x1005498a8), *p: (5), &p: (0x7ffeefbff290)
 sp: (0x1005498a8), *sp: (5), &sp: (0x7ffeefbff280)
 
 C++ Primer(14053,0x1000dfdc0) malloc: *** error for object 0x1005498a8: pointer being freed was not allocated
 */

#include <memory>
#include <iostream>

int main()
{
    int x = 5;
    
    // dynamically value-allocate a smart int pointer to 0
    auto sp = std::make_shared<int>();
    *sp = x;
    
    // assigning a smart pointer to a pointer...
    auto p = sp.get();
    
    std::cout << "Using x (" << x << ") as test variables." << std::endl;
    
    std::cout << "\np: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;
    std::cout << "sp: (" << sp << "), *sp: (" << *sp << "), &sp: (" << &sp << ")" << std::endl;
    std::cout << "sp has " << sp.use_count() << ((sp.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
    
    //
    // delete p
    //
    // this is not ideal
    // when the code exits, "sp" will try and free a memory address that has already been freed (see output)
    //

    return 0;
}
