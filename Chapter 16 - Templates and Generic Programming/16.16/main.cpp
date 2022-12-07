// Exercise 16.16:
/*
 Rewrite the StrVec class (§ 13.5, p. 526) as a template named Vec.
*/

#include "Vec.h"
#include <string>
#include <iostream>

int main()
{
    Vec<std::string> svec = { "man" };
    svec.push_back("bear");
    svec.push_back("pig");
    printVec(svec);
    std::cout << "Size of svec: " << svec.size() << std::endl << std::endl;
    
    Vec<int> ivec = { 0, 1, 2 };
    ivec.push_back(3);
    ivec.push_back(4);
    ivec.push_back(5);
    printVec(ivec);
    std::cout << "Size of ivec: " << svec.size() << std::endl << std::endl;
    
    return 0;
}
