// Exercise 16.56:
/*
 Write and test a variadic version of errorMsg.
*/

#include <iostream>
#include <string>
#include <sstream>

template <typename T> std::string debug_rep(const T &t) {
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> std::string debug_rep(T* p) {
    std::ostringstream ret;
    ret << "pointer: " << p;
    
    ret << " " << (p ? "(" + debug_rep(*p) + ")" : "null pointer" ) << "\n";
    return ret.str();
}

std::string debug_rep(const std::string &s) { return '"' + s + '"'; }

std::string debug_rep(char *c) { return debug_rep(std::string(c)); }

std::string debug_rep(const char *c) { return debug_rep(std::string(c)); }

template <typename T>
std::ostream& print(std::ostream &os, const T &t) { return os << t << " "; }

template <typename T, typename ...Args>
std::ostream& print(std::ostream &os, const T &t, const Args &...rest) {
    os << t << " ";
    return print(std::cout, rest...);
}

template <typename ...Args>
std::ostream& errorMsg(std::ostream &os, const Args &...rest)
{
    return print(os, debug_rep(rest)...);
}

int main()
{
    errorMsg(std::cout, 404, "page not found") << std::endl;
    
    return 0;
}
