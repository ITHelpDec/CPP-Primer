// Exercise 12.12:
/*
 Using the declarations of p and sp explain each of the following calls to process.
 If the call is legal, explain what it does.
 If the call is illegal, explain why:
*/

#include <memory>
#include <iostream>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "\nptr: (" << ptr << "), *ptr: (" << *ptr << "), &ptr: (" << &ptr << ")" << std::endl;
    std::cout << "ptr has " << ptr.use_count() << ((ptr.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
} // ptr goes out of scope and is destroyed

int main()
{
    int x = 5, y = 10;
    
    // dynamically value allocate a new int (should initialise at 0)
    auto p = new int();
    *p = x;
    
    // dynamically value-allocate a smart pointer (similar outcome)
    auto sp = std::make_shared<int>();
    *sp = y;
    
    std::cout << "Using x (" << x << ") and y (" << y << ") as test variables." << std::endl;
    
    std::cout << "\np: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;
    std::cout << "sp: (" << sp << "), *sp: (" << *sp << "), &sp: (" << &sp << ")" << std::endl;
    std::cout << "sp has " << sp.use_count() << ((sp.use_count() == 1) ? " occurence." : " occurences.") << std::endl;
    
    // (a)
    // create shared pointer of shared pointer
    // count will increase by 1, then be freed
    process(sp);
    std::cout << "\np: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;
    std::cout << "sp: (" << sp << "), *sp: (" << *sp << "), &sp: (" << &sp << ")" << std::endl;
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
    // legal, but not ideal
    // std::shared_ptr<int>(p) will initialise a shared_ptr using the ordinary pointer "p"
    // reference count increases to 1
    // once it is pushed through process, reference count decreases to 0,
    // which in turn frees the memory pointed to by "ptr"
    // However, the original pointer "p" still points to this memory address
    // p is now a dangling pointer
    process(std::shared_ptr<int>(p));
    
    std::cout << "\np: (" << p << "), *p: (" << *p << "), &p: (" << &p << ")" << std::endl;
    std::cout << "sp: (" << sp << "), *sp: (" << *sp << "), &sp: (" << &sp << ")" << std::endl;

    return 0;
}
