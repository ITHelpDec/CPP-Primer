#include <memory>

void foo()
{
    // two dynamically allocation pointers are created – q and r
    // q points to an int with value 42; r points to an int with value 100
    int *q = new int(42), *r = new int(100);
    
    // r now points to the location of q
    // the old memory pointed to by r has now been leaked, since no other points point to it, and it has not been freed
    r = q;
    
    // two shared pointers are created, pointing to similar values as above
    auto q2 = std::make_shared<int>(42), r2 = std::make_shared<int>(100);
    
    // assign q2 to r2
    // increase use count of q2 from 1 to 2
    // decrease use count of r2 from 1 to 0
    // because the object r2 had pointed to has no users, the object is now automatically freed from memory
    r2 = q2;
}
