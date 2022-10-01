// Exercise 12.11:
/*
 What would happen if we called process as follows?
*/

#include <memory>
#include <iostream>

void process(std::shared_ptr<int> ptr)
{
    // use ptr
} // ptr goes out of scope and is destroyed

int main()
{
    // as before
    std::shared_ptr<int> p(new int(42));
    
    // error for object 0x10041e200:
    // pointer being freed was not allocated
    process(std::shared_ptr<int>(p.get()));
    
    return 0;
}

// general advice is to not use .get() to initialise or assigned another smart pointer
// in the case above, this will create two shared_ptr pointers that, although point to the same memory address, are independent of each other, and do not impact occurences
// when the block in which the second shared_ptr is defined ends, this shared_ptr will be destroyed
// Destroying this shared_ptr frees the memory to which the shared_ptr points
// That makes p into a dangling pointer, meaning that what happened when we might attempt to use p is unidentified.
// Moreoever, when p is destroyed, the pointer to that memory will be deleted a second time
//
// !!!NEVER USE GET TO INITIALISE OR ASSIGN TO ANOTHER SMART POINTER !!!
//
