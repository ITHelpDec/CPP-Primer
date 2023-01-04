// Exercise 19.02:
/*
 By default, the allocator class uses operator new to obtain storage and operator delete to free it.
 Recompile and rerun your StrVec programs (§ 13.5, p. 526) using your versions of the functions from the previous exercise.
*/

#include "StrVec.hpp"

int main()
{
    std::cout << "Allocating StrVec on the stack...\n";
    StrVec svec = { "man", "bear", "pig" };
    printVec(svec);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "\nAllocating StrVec on the heap...\n";
    StrVec *svp = new StrVec({ "half man,", " half bear,", " half pig" });
    printVec(*svp);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
    std::cout << "\nDeleting dynamically-allocated StrVec from the heap...\n";
    delete svp;
  
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << std::endl;
    
    return 0;
}

// output:

// Allocating StrVec on the stack...

// Printing vector...
// manbearpig

// Allocating StrVec on the heap...
// void *operator new(std::size_t)

// Printing vector...
// half man, half bear, half pig

// Deleting dynamically-allocated StrVec from the heap...
// void operator delete(void*) noexcept

// Program ended with exit code: 0
