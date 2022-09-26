// Exercise 12.12:
/*
 Using the declarations of p and sp explain each of the following calls to process.
 If the call is legal, explain what it does.
 If the call is illegal, explain why:
*/

/* Output:
 Using x (5) and y (10) as test variables.

 p: (0x10288a1a0), *p: (5), &p: (0x7ffeefbff290)
 sp: (0x102895788), *sp: (10), &sp: (0x7ffeefbff280)
 sp has 1 occurence.

 ptr: (0x102895788), *ptr: (10), &ptr: (0x7ffeefbff270)
 ptr has 2 occurences.

 p: (0x10288a1a0), *p: (5), &p: (0x7ffeefbff290)
 sp: (0x102895788), *sp: (10), &sp: (0x7ffeefbff280)
 sp has 1 occurence.

 ptr: (0x10288a1a0), *ptr: (5), &ptr: (0x7ffeefbff260)
 ptr has 1 occurence.

 p: (0x10288a1a0), *p: (0), &p: (0x7ffeefbff290)
 sp: (0x102895788), *sp: (10), &sp: (0x7ffeefbff280)
 Program ended with exit code: 0
 */

#include <memory>
#include <iostream>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "ptr: (" << ptr << "), *ptr: (" << *ptr << "), &ptr: (" << &ptr << ")" << std::endl;
    std::cout << "ptr has " << ptr.use_count() << ((ptr.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
} // ptr goes out of scope and is destroyed

int main()
{
    // dynamically value allocate a new int (should initialise at 0)
    auto p = new int();
    std::cout << "p: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;
    
    // dynamically value-allocate a smart pointer (similar outcome)
    auto sp = std::make_shared<int>();
    std::cout << "sp: (" << sp << "), *sp: (" << *sp << "), &sp: (" << &sp << ")" << std::endl;
    std::cout << "sp has " << sp.use_count() << ((sp.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
    
    // (a)
    // create shared pointer of shared pointer
    // count will increase by 1, then be freed
    process(sp);
    std::cout << "sp has " << sp.use_count() << ((sp.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
    
    // (b)
    // error: cannot convert int* to shared_ptr<int>
    // process(int new());
    
    // (c)
    // function will only take a shared_ptr
    // error: cannot convert int* to shared_ptr<int>
    // process(p);
    
    // (d)
    // std::shared_ptr<int>(p)
    process(std::shared_ptr<int>(p));
    
    std::cout << "p: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;

    return 0;
}
