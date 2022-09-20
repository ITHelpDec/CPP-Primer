// Exercise 10.24:
/*
 Use bind and check_size to find the first element in a vector of ints that has a value greater than the length of a specified string value.
 
 >> This exercise was quite temperamental...semantic errors that came and went...
*/

#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>

// true if
bool check_size(const std::string &s, const std::string::size_type &sz)
// bool check_size(const std::string &s, std::string::size_type &sz)
{
    return sz > s.size();
}

void first_greater(const std::vector<int> &ivec, const std::string &s)
{
    auto first_greater_pos = std::find_if(ivec.cbegin(), ivec.cend(), std::bind(check_size, s, std::placeholders::_1));
    std::cout << "The first largest number greater than the length of \"" << s << "\" (" << s.size() << ") is " << *first_greater_pos << " – ivec[" << first_greater_pos - ivec.cbegin() << "]" << std::endl;
}

int main()
{
    // create vector of ints and comparison string
    std::vector<int> ivec = { 5, 2, 4, 8, 4, 8, 11, 9};
    std::string s = "manbearpigs";
    
    // find first value greater than thn s.size()
    first_greater(ivec, s);
    
    
    return 0;
}
