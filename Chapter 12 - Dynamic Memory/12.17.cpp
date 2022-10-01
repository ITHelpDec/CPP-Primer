// Exercise 12.17:
/*
 Which of the following unique_ptr declarations are illegal or likely to result in subsequent program error?
 Explain what the problem is with each one.
*/

#include <memory>
#include <iostream>

int main()
{
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);
    typedef std::unique_ptr<int> IntP;
    
    // (a)
    // illegal: ix is not a pointer
    // "No matching constructor for initialisation of std::unique_ptr<int>"
    // Trying to make a unique pointer out of an integer
    //
    // IntP p0(ix);
    
    // (b)
    // illegal: "pi" is not a dynamically-allocated pointer, therefore it cannot be used by a smart pointer
    // std::unique_ptr<int> p1(&ix);
    // throws error message "pointer being freed was not allocated"
    //
    // IntP p1(pi);
    
    // (c)
    // std::unique_ptr<int> p2(new int(2048));
    // legal: pi2 is a dynamically-allocated
    // if "p2" is destroyed, "pi2" should not be used to access that memory location again
    IntP p2(pi2);
    std::cout << "pi2: " << pi2 << ", *pi2: " << *pi2 << std::endl;
    std::cout << "p2: " << p2 << ", *p2: " << *p2 << std::endl;
    
    // (d)
    // illegal: like (b), cannot assign a non-dynamically-allocated to a smart pointer
    // std::unique_ptr<int> p3(&ix)
    //
    // IntP p3(&ix);
    
    // (e)
    // std::unique_ptr<int> p4(new int(2048));
    // legal: dynamically-allocated
    IntP p4(new int(2048));
    std::cout << "p4: " << p4 << ", *p4: " << *p4 << std::endl;
    
    // (f)
    // std::unique_ptr<int> p5(p2.get());
    // "don't use get() to initialise or reset another smart pointer"
    // in this case, two unique_ptr's would point to the same memory address
    // memory would be freed twice when desroyed and throw errors
    // "ointer being freed was not allocated"
    //
    // IntP p5(p2.get());
}
