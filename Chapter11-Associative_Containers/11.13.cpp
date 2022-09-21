// Exercise 11.13:
/*
 There are at least three ways to create the pairs in the program for the previous exercise.
 Write three versions of that program, creating the pairs in each way.
 Explain which form you think is easiest to write and understand, and why.
 
 >> I prefer the curly braces
*/

#include <utility>
#include <iostream>

int main()
{
    int x = 1, y = 2;

    std::pair<int, int> ip1 = { x, y };
    std::pair<int, int> ip2 = std::make_pair(x, y);
    std::pair<int, int> ip3;
    ip3.first = x;
    ip3.second = y;

    std::cout << "ip1: (" << ip1.first << ", " << ip1.second << ")" <<std::endl;
    std::cout << "ip2: (" << ip2.first << ", " << ip2.second << ")" <<std::endl;
    std::cout << "ip3: (" << ip3.first << ", " << ip3.second << ")" <<std::endl;
    
    return 0;
}
