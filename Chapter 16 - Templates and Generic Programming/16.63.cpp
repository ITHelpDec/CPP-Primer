// Exercise 16.63:
/*
 Define a function template to count the number of occurrences of a given value in a vector.
 Test your program by passing it a vector of doubles, a vector of ints, and a vector of strings.
*/

#include <iostream>
#include <vector>
#include <string>

// const T& version to lower memory footprint
template <typename T>
std::size_t vcount(const std::vector<T> &tvec, const T &val) {
    std::size_t count = 0;
    
    for (const auto &t : tvec)
        if (t == val) { ++count; }
    
    return count;
}

// specialisation for string literals
// without unsigned N, we would need to create a non-const T val version...
// ...and refer to const char* const &cstr, to avoid ambiuguity
// this would however increase memory footprint
template <unsigned N>
std::size_t vcount(const std::vector<const char*> &csvec, const char (&cstr)[N]) {
    std::size_t count = 0;
    
    for (const auto &s : csvec)
        if (!strcmp(s, cstr)) { ++count; }
    
    return count;
}

int main()
{
    double d = 3.14;
    std::cout << "std::vector<double>: ";
    std::vector<double> dvec = { 3.14, 2.42, 3.14, 6.43, 6.57, 8.54, 3.14 };
    std::cout << d << " appears " << vcount(dvec, d) << " times." << std::endl;
    
    int val = 4;
    std::cout << "std::vector<int>: ";
    std::vector<int> ivec = { 0, 1, 2, 3, 4, 3, 4, 2, 5, 1, 0 };
    std::cout << val << " appears " << vcount(ivec, val) << " times." << std::endl;
    
    std::string s = "half";
    std::cout << "std::vector<std::string>: ";
    std::vector<std::string> svec = { "half", "man", "half", "bear", "half", "pig" };
    std::cout << s << " appears " << vcount(svec, s) << " times." << std::endl;
    
    std::cout << "std::vector<const char*>: ";
    std::vector<const char*> csvec = { "half", "man", "half", "bear", "half", "pig" };
    std::cout << s << " appears " << vcount(csvec, "half") << " times." << std::endl;
    
    return 0;
}

// output:
// std::vector<int>: 4 appears 2 times.
// std::vector<double>: 3.14 appears 3 times.
// std::vector<std::string>: half appears 3 times.
// std::vector<const char*>: half appears 3 times.
// Program ended with exit code: 0