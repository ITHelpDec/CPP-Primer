// Exercise 9.31:
/*
 The program on page 354 to remove even-valued elements and duplicate odd ones will not work on a list or forward_list.
 Why?
 Revise the program so that it works on these types as well.
 
 // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements
 vector<int> vi = {0,1,2,3,4,5,6,7,8,9};
 autoiter = vi.begin();
 
 // call begin,not cbegin because we’re changing vi
 while (iter != vi.end())
 {
    if (*iter % 2) {
        // duplicate the current element
        iter = vi.insert(iter, *iter);
        
        // advance past this element and the one inserted before it
        iter += 2;
    } else
        // remove even elements
        iter = vi.erase(iter);
        // don’t advance the iterator; iter denotes the element after the one we erased
 }
 
 */

#include <list>
#include <forward_list>
#include <iostream>

void list2odds(std::list<int> &il)
{
    // create non-const iterator
    std::list<int>::iterator pos = il.begin();
    
    while (pos != il.end())
    {
       if (*pos % 2) {
           // duplicate the current element
           pos = il.insert(pos, *pos);
           
           // advance past this element and the one inserted before it
           // pos += 2 does not seem to work; std::advance(iter, n) produces a similar result
           std::advance(pos, 2);
       } else
           // remove even elements
           pos = il.erase(pos);
           // don’t advance the iterator; iter denotes the element after the one we erased
    }
}

void flist2odds(std::forward_list<int> &ifl)
{
    // create non-const iterator for curr and prev
    std::forward_list<int>::iterator curr = ifl.begin();
    std::forward_list<int>::iterator prev = ifl.before_begin();
    
    while (curr != ifl.end())
    {
       if (*curr % 2) {
           // duplicate the current element
           prev = ifl.insert_after(prev, *curr);
           ++curr, ++prev;
       } else {
           // remove current element (even number)
           curr = ifl.erase_after(prev);
       }
    }
}

int main()
{
    // create list of integers to test
    std::cout << "Before..." << std::endl;
    std::list<int> il = {0, 1, 2, 3, 4, 5};
    std::forward_list<int> ifl = {0, 1, 2, 3, 4, 5};
    
    // view current values
    std::cout << "il: ";
    for (const auto &e : il)
        std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "ifl: ";
    for (const auto &e : ifl)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // change all even elements to odd
    list2odds(il);
    flist2odds(ifl);
    
    // view new values
    std::cout << "After..." << std::endl;
    
    std::cout << "il: ";
    for (const auto &e : il)
        std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "ifl: ";
    for (const auto &e : ifl)
        std::cout << e << " ";
    std::cout << std::endl;
    
    return 0;
}
