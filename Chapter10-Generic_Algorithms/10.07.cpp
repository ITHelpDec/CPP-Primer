// Exercise 10.07:
/*
 Determine if there are any errors in the following programs and, if so, correct the error(s):
 
 (a)
 vector<int> vec;
 list<int> lst;
 int i;
 
 while (cin >> i)
    lst.push_back(i);
 
 copy(lst.cbegin(), lst.cend(), vec.begin());
 
 (b)
 vector<int> vec;
 vec.reserve(10); // reserve is covered in § 9.4 (p. 356)
 fill_n(vec.begin(), 10, 0);
*/

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>

void a(std::vector<int> &ivec, std::list<int> &ilist)
{
    int i;
    
    while (std::cin >> i)
        ilist.push_back(i);
    // copy will only work if both containers are of the same size
    ivec.resize(ilist.size());
    copy(ilist.cbegin(), ilist.cend(), ivec.begin());
}

void b(std::vector<int> &ivec)
{
    ivec.reserve(10); // reserve is covered in § 9.4 (p. 356)
    // will not fill in without back_inserter
    // std::fill_n(ivec.begin(), 10, 0);
    std::fill_n(std::back_inserter(ivec), 10, 0);
}

int main()
{
    // create blank vectors for tests
    std::vector<int> iveca, ivecb;
    std::list<int> ilist;
    
    // print initial results
    std::cout << "ilist: ";
    for (const auto &e : ilist)
        std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "ivec: ";
    for (const auto &e : iveca)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // perform function a
    a(iveca, ilist);
    
    // re-print results
    std::cout << "ilist: ";
    for (const auto &e : ilist)
        std::cout << e << " ";
    std::cout << std::endl;
    
    std::cout << "iveca: ";
    for (const auto &e : iveca)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // perform function b
    b(ivecb);
    
    // print results
    std::cout << "ivecb: ";
    for (const auto &e : ivecb)
        std::cout << e << " ";
    std::cout << std::endl;
    
    return 0;
}
