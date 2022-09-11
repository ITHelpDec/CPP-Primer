// Exercise 9.20:
/*
 Write a program to copy elements from a list<int> into two deques.
 The even-valued elements should go into one deque and the odd ones into the other.
*/

#include <list>
#include <deque>
#include <iostream>

int main()
{
    // create list of integers
    std::list<int> il = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::cout << "Printing integer list...: ";
    for (auto &e : il)
        std::cout << e << " ";
    
    // create two blank deques to copy integers to
    std::deque<int> dqeven, dqodd;
    
    // separate even and odd numbers
    std::cout << std::endl << "Separating odd and even numbers into deque's...";
    for (auto &e : il)
        if (e % 2 == 0)
            dqeven.push_back(e);
        else
            dqodd.push_back(e);
    
    // print results
    std::cout << std::endl << "dqeven contains: ";
    for (auto &e : dqeven)
        std::cout << e << " ";
    
    std::cout << std::endl << "dqodd contains: ";
    for (auto &e : dqodd)
        std::cout << e << " ";
    
    std::cout << std::endl;
    return 0;
}
