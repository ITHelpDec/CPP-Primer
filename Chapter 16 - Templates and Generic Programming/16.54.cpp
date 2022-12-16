// Exercise 16.54:
/*
 What happens if we call print on a type that doesn’t have an << operator?
 
 >> It will not print as is, but we can rewrite like below.
*/

#include <iostream>
#include <vector>

template <typename T> std::ostream& print(std::ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename ...Args> std::ostream& print(std::ostream &os, const T &t, const Args& ...rest) {
    os << t << " ";
    return print(os, rest...);
}

int main()
{
    std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    
    // will not run
    // print(std::cout, ivec);
    
    for (const auto &e : ivec) {
        print(std::cout, e) << " ";
    } std::cout << std::endl;
    
    return 0;
}
