// Example 16.04:
/*
 Write a template that acts like the library find algorithm.
 The function will need two template type parameters;
 One to represent the function’s iterator parameters and the other for the type of the value. Use your function to find a given value in a vector<int> and in a list<string>.
*/

#include <vector>
#include <list>
#include <string>
#include <iostream>

// official std::find() implementation
// https://en.cppreference.com/w/cpp/algorithm/find
template <class InputIt, class T> constexpr InputIt templateFind(InputIt first, InputIt last, const T &value) {
    for ( ; first != last; ++first)
        if (*first == value) { return first; }
    return last;
}

int main()
{
    std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    int x = 4, y = 6;
    auto ivec_test1 = templateFind(ivec.begin(), ivec.end(), x);
    auto ivec_test2 = templateFind(ivec.begin(), ivec.end(), y);
    
    // should create another template to condense this output
    std::cout << x << " was " << (ivec_test1 == ivec.end() ? "not " : "") << "found in our vector.\n";
    if (ivec_test1 != ivec.end())
        std::cout << "Its position is element number " << ivec_test1 - ivec.begin() + 1 << " of " << ivec.size() << std::endl;
    
    std::cout << y << " was " << (ivec_test2 == ivec.end() ? "not " : "") << "found in our vector.\n";
    if (ivec_test2 != ivec.end())
        std::cout << "Its position is element number " << ivec_test1 - ivec.begin() + 1 << " of " << ivec.size() << std::endl;
    
    std::cout << std::endl;
    
    std::list<std::string> svec = { "man", "bear", "pig" };
    std::string s1 = "man", s2 = "half";
    auto svec_test1 = templateFind(svec.begin(), svec.end(), s1);
    auto svec_test2 = templateFind(svec.begin(), svec.end(), s2);
    
    std::cout << s1 << " was " << (ivec_test1 == ivec.end() ? "not " : "") << "found in our list.\n";
    if (svec_test1 != svec.end())
        std::cout << "Its position is element number " << std::distance(svec.begin(), svec_test1) + 1 << " of " << svec.size() << std::endl;
    
    std::cout << s2 << " was " << (svec_test2 == svec.end() ? "not " : "") << "found in our list.\n";
    if (svec_test2 != svec.end())
        std::cout << "Its position is element number " << std::distance(svec.begin(), svec_test1) + 1<< " of " << svec.size() << std::endl;
    
    std::cout << std::endl;
    
    return 0;
}
