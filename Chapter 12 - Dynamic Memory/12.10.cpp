// Exercise 12.08:
/*
 Explain whether the following call to the process function defined on page 464 is correct.
 If not, how would you correct the call?
*/

#include <memory>

int main()
{
    // process count is one on the below code
    std::shared_ptr<int> p(new int(42));
    
    // this is correct
    std::process(std::shared_ptr<int>(p));
    
    // copying a shared_ptr incremenets its reference count
    // (would be a different scenario if the above code were a normal pointer
    
    // "When process completes, the reference count of the shared_ptr is decremented,
    // but cannot go to zero
    // Therefore, when the local variable "p" is destroyed,
    // the memory to which p points will not be deleted."
    
    return 0;
}
