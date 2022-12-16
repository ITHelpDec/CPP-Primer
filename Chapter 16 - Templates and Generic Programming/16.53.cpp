// Exercise 16.53:
/*
 Write your own version of the print functions and test them by printing one, two, and five arguments, each of which should have different types.
*/

#include <iostream>
#include <string>

template <typename T> std::ostream& print(std::ostream &os, const T &t) {
    return os << t;
}

template <typename T, typename ...Args> std::ostream& print(std::ostream &os, const T &t, const Args& ...rest) {
    os << t << " ";
    return print(os, rest...);
}

int main()
{
    int i = 1;
    double d = 3.14;
    std::string s = "manbearpig";
    
    std::cout << "print(1 arg):  ";
    print(std::cout, 42);
    std::cout << std::endl;
    
    std::cout << "print(2 args): ";
    print(std::cout, "hi", d);
    std::cout << std::endl;
    
    std::cout << "print(5 args): ";
    print(std::cout, i, d, s, 2, "halfmanhalfbearhalfpig");
    std::cout << std::endl;
    
    return 0;
}
