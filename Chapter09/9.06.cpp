// Exercise 9.06:
/*
 What is wrong with the following program?
 How might you correct it?
 
 list<int> lst1;
 list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
 while (iter1 < iter2) {}
 
 >> Safer to use != instead of <
 >> Do lists also not support arithmetic operators like "<" and ">"?
*/

#include <list>
#include <iostream>

int main()
{
    std::list<int> lst1 = {1, 2, 3, 4, 5};

    std::list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();

    while (iter1 != iter2) {
        std::cout << *iter1 << std::endl;
        ++*iter1;
    }
    
    return 0;
}
