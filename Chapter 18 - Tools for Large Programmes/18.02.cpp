// Exercise 18.02:
/*
 Explain what happens if an exception occurs at the indicated point:
*/

#include <vector>
#include <fstream>
#include <stdexcept>

void exercise(int *b, int *e) {
    // "On the other hand, resources allocated by an object of class type...
    // ...will generally be freed by their destructor." – pg. 774
    //
    // ~vector() called
    std::vector<int> ivec(b, e);
    
    // "..., if a block allocates a resource, and an exception occurs before...
    // ...the code that frees that resource, the code to free the resource...
    // ..will not be executed" – pg. 774
    //
    // I believe this will cause a memory leak, as "the code to free the...
    // ...(dynamically-allocated) resource will not be executed"
    int *p = new int[ivec.size()];
    
    // "On the other hand, resources allocated by an object of class type...
    // ...will generally be freed by their destructor." – pg. 774
    //
    // ~ifstream() called
    std::ifstream file("ints");
    
    // exception occurs here
    
    throw std::exception();
    // begin unwinding the stack and terminate if not throw not caught
    //
    // libc++abi: terminating with uncaught exception of type std::exception: std::exception
    // terminating with uncaught exception of type std::exception: std::exception
}

int main()
{
    int beg = 3, end = 5;
    
    exercise(&beg, &end);
    
    return 0;
}
