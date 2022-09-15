// Exercise 10.02:
/*
 Repeat the previous program, but read values into a list of strings.
 
 >> Again, would be nice to programme something for duplicates
*/

#include <list>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    // create empty vector to store integer input
    //std::vector<int> ivec;
    std::list<std::string> slist;
    
    // int number = 0;
    std::string s;
    
    // take input until eof
    while (std::cin >> s)
        slist.push_back(s);
    
    std::cout << std::endl;
    
    for (const auto &e : slist)
        std::cout << e << " ";
    
    for (const auto &e : slist)
        std::cout << e << " appears " << std::count(slist.begin(), slist.end(), e) << " time(s)." << std::endl;
    
    return 0;
}

