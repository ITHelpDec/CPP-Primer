// Exercise 16.02:
/*
 Write and test your own versions of the compare functions.
*/

#include <string>
#include <iostream>

// returns 0 if the values are equal
// -1 if v1 is smaller, 1 if v2 is smaller
int compare(const std::string &v1, const std::string &v2) {
    return v1 < v2 ? -1 : v2 < v1 ? 1 : 0;
}

int compare(const double &v1, const double &v2) {
    return v1 < v2 ? -1 : v2 < v1 ? 1 : 0;
}

// functions above are identical, bar their parameter types
// work can be condensed using a template
template <typename T>
int compare(const T &v1, const T &v2) {
    return v1 < v2 ? -1 : v2 < v1 ? 1 : 0;
}

int main()
{
    std::cout << compare(0, 1) << std::endl;
    std::cout << compare({ 1, 2, 3 }, { 1, 1, 3 }) << std::endl;
    
    return 0;
}

// helpful for variable length c-style strings
template <unsigned N, unsigned M>
int compare(const char (&p1) [N], const char (&p2) [M]) {
    return strcmp(p1, p2);
}

int main()
{
    std::cout << compare("man", "man") << std::endl;;
    std::cout << compare("bear", "pig") << std::endl;
    
    return 0;
}
*/

// inline goes after the template parameter list
template <typename T> inline T min(const T&, const T&) { }
// inline std::vector<int> min(const std::vector<int>&, const std:;vector<int>&) { }

#include <functional>

// using "<" can limit the types we can use
// take advantage of std::less<>() if worried about independence and portabiltity
template <typename T> int compare(const T &v1, const T &v2) {
    return std::less<T>()(v1, v2) ? -1 : std::less<T>()(v2, v1) ? 1 : 0;
}

int main()
{
    std::cout << compare(1, 9) << std::endl;
    std::cout << compare(10, 9) << std::endl;
    std::cout << compare(19, 19) << std::endl;
    
    return 0;
}

