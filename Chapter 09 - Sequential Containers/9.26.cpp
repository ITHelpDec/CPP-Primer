// Exercise 9.26:
/*
 Using the following definition of ia, copy ia into a vector and into a list.
 Use the single-iterator form of erase to remove the elements with odd values from your list and the even values from your vector.
 
 int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
 */

#include <vector>
#include <iostream>
#include <list>

int main()
{
    // array of integers
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
    std::cout << "ia: ";
    for (const auto &e : ia)
        std::cout << e << " ";
    
    // copy elements using iterator shorthand
    std::cout << std::endl << "Copying elements...";
    std::vector<int> ivec(std::begin(ia), std::end(ia));
    std::list<int> ilist(std::begin(ia), std::end(ia));

    // display results
    std::cout << std::endl << "ilist: ";
    for (const auto &e : ilist)
        std::cout << e << " ";
    std::cout << std::endl << "ivec: ";
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    // remove odds from list and evens from vector using single iterator
    std::cout << std::endl << "Removing odds and evens...";
    auto poslist = ilist.begin();
    auto posvec = ivec.begin();
    
    while (poslist != ilist.end() && posvec != ivec.end()) {
        if (*poslist % 2) {
            poslist = ilist.erase(poslist);
            ++posvec;
        } else {
            posvec = ivec.erase(posvec);
            ++poslist;
        }
    }
    
    // display new for list and vector
    std::cout << std::endl << "ilist: ";
    for (const auto &e : ilist)
        std::cout << e << " ";
    std::cout << std::endl << "ivec: ";
    for (const auto &e : ivec)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    return 0;
}
