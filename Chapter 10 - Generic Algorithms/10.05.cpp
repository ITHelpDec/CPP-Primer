// Exercise 10.05:
/*
 In the call to equal on rosters, what would happen if both rosters held C-style strings, rather than library strings?
 
 >> Nothing different would happen – main thing is that the containers have the same
*/

#include <vector>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<const char *> roster1 = { "man", "bear", "pig" };
    std::vector<const char *> roster2 = { "man", "bear", "pig" };
    
    bool areEqual = std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin());
    
    std::cout << "Both vectors are " << (areEqual ? "equal.": "not equal.") << std::endl;
    
    return 0;
}
