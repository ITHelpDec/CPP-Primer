// Exercise 10.28:
/*
 Copy a vector that holds the values from 1 to 9 inclusive, into three other containers.
 Use an inserter, a back_inserter, and a front_inserter, respectively to add elements to these containers.
 Predict how the output sequence varies by the kind of inserter and verify your predictions by running your programs.
*/

#include <vector>
#include <forward_list>
#include <list>
#include <deque>
#include <iostream>

// il: 1 2 3 4 5 6 7 8 9
void insert_to_list(const std::vector<int> &ivec)
{
    // create forward list and insert bits
    std::list<int> il;
    
    // copy elements
    std::copy(ivec.cbegin(), ivec.cend(), std::inserter(il, il.begin()));
    
    // print results
    std::cout << "il: ";
    for (const auto &e : il) std::cout << e << " ";
    std::cout << std::endl;
}

// idq: 1 2 3 4 5 6 7 8 9
void back_insert_to__deque(const std::vector<int> &ivec)
{
    // create deque and insert bits
    std::deque<int> idq;
    
    // copy elements
    std::copy(ivec.cbegin(), ivec.cend(), std::back_inserter(idq));
    
    // print results
    std::cout << "idq: ";
    for (const auto &e : idq) std::cout << e << " ";
    std::cout << std::endl;
}

// fil: 1 2 3 4 5 6 7 8 9
// used crbegin and crend to reverse direction of iterator
// cbegin and cend would produce "fil: 9 8 7 6 5 4 3 2 1"
void front_insert_to__forward_list(const std::vector<int> &ivec)
{
    // create list and insert bits
    std::forward_list<int> fil;
    
    // copy elements
    std::copy(ivec.crbegin(), ivec.crend(), std::front_inserter(fil));
    
    // print results
    std::cout << "fil: ";
    for (const auto &e : fil) std::cout << e << " ";
    std::cout << std::endl;
}

int main()
{
    std::vector<int> ivec = { 1, 2, 3 ,4 ,5, 6, 7 ,8, 9 };
    // print results
    std::cout << "ivec: ";
    for (const auto &e : ivec) std::cout << e << " ";
    std::cout << std::endl;
    
    insert_to_list(ivec);
    
    back_insert_to__deque(ivec);
    
    front_insert_to__forward_list(ivec);
    
    return 0;
}
