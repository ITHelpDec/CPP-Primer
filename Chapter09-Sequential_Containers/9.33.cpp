// Exercise 9.33:
/*
 In the final example in this section what would happen if we did not assign the result of insert to begin?
 Write a program that omits this assignment to see if your expectation was correct.

 // safer: recalculate end on each trip whenever the loop adds/erases elements
 while (begin != v.end())
 {
    // do some processing
    // advance begin because we want to insert after this element
    ++begin;
 
    // insert the new value
    begin = v.insert(begin, 42);
    
    // advance begin past the element we just added
    ++begin;
 }
*/

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> v = { 0, 1, 2, 3, 4, 5 };
    auto begin = v.begin();
    
    while (begin != v.end())
    {
        ++begin;
        // begin = v.insert(begin, 42);
        
        // if we were to run the insert without the assignment the computer would cause run-time issues
        // v.insert(begin, 42);
        
        ++begin;
        
        // if we were to avoid the line entirely, the the loop would just iterate over the odd numbers of the vector
        // std::cout << *begin << " ";
    }
    
    return 0;
}
