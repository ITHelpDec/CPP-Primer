// Exercise 16.39:
/*
 Use an explicit template argument to make it sensible to pass two string literals to the original version of compare from § 16.1.1 (p. 652).
*/

#include <string>
#include <iostream>

template <typename T> int compare(const T &t1, const T &t2) {
    return t1 < t2 ? -1 : t2 < t1 ? 1 : 0;
}

int main()
{
    std::cout << compare<std::string>("half", "man") << std::endl;
    std::cout << compare<std::string>("half", "bear") << std::endl;
    std::cout << compare<std::string>("half pig", "half pig") << std::endl;
    
    return 0;
}

