// Exercise 18.05:
/*
 Modify the following main function to catch any of the exception types shown in Figure 18.1 (p. 783):
 
 The handlers should print the error message associated with the exception before call- ing abort (defined in the header cstdlib) to terminate main.

 >> Another rubbish question – they really should give more examples
 
 >> We can use the previous vague exercise as a a testcase, as it threw a length_error if you used pointers to integers instead integer arrays
 >> A custom message is also far more helpful than trying to interpret "std::length_error"
 
 // std::abort() freezes at "signal SIGABRT" – there is a handler on cppreference, but this isn't covered in the book yet...
*/

/* .:. HIERARCHY .:. */
/*
                     exception
                   /   /   \   \
                  /   /     \   \
          bad_cast   /       \   bad_alloc
                    /         \
      runtime_error            logic_error
                  |            |
 overflow_error---|            |---domain_error
                  |            |
underflow_error---|            |---invalid_argument
                  |            |
    range_error---|            |---out_of_range
                               |
                               |---length_error
 
*/

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstdlib>

void exercise(int *b, int *e) {
    std::vector<int> ivec(b, e);
    int *p = new int[ivec.size()];
    std::ifstream file("ints");
    // exception occurs here
}

int main()
{
    int beg = 3, end = 5;
    
    try {
        exercise(&beg, &end);
    } catch (std::length_error e){
        std::cerr << "std::length_error: " << e.what() << "\n>>> a and b need to be arrays, not pointers to integers." << std::endl;
        std::abort();
    } // signal SIABRT
    
    return 0;
}
