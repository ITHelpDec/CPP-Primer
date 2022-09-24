// Exercise 11.26:
/*
 What type can be used to subscript a map? What type does the subscript operator return?
 >> a ::key_type can be used to sbscript a map
 >> the subscript operator will return the mapped_type
 
 Give a concrete example – that is, define a map and then write the types that can be used to subscript the map and the type that would be returned from the subscript operator.
 */

#include <map>
#include <iostream>

int main()
{
    std::map<int, int> imap = {
        {0,1},
        {2,3}
    };
    
    std::cout << imap.at(0) << std::endl;
    std::cout << imap[2] << std::endl;
    
    return 0;
}
