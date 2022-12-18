// Exercise 16.65:
/*
 In § 16.3 (p. 698) we defined overloaded two versions of debug_rep one had a const char* and the other a char* parameter.
 Rewrite these functions as specializations.
*/

#include <string>
#include <sstream>
#include <iostream>

template <typename T> std::string debug_rep(const T& t) {
    std::cout << "debug_rep(const T &t)" << std::endl;
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename Tp> std::string debug_rep(Tp *p) {
    std::cout << "debug_rep(Tp *p)" << std::endl;
    std::ostringstream ret;
    ret << "pointer: " << p;
    
    ret << " " << (p ? debug_rep(*p) : "null pointer.\n");
    
    return ret.str();
}

// char *cstr specialisation
template <> std::string debug_rep(char *cstr) {
    std::cout << "debug_rep(char *cstr)" << std::endl;
    return debug_rep(std::string(cstr));
}

// const char *cstr specialisation
template <> std::string debug_rep(const char *cstr) {
    std::cout << "debug_rep(const char *cstr)" << std::endl;
    return debug_rep(std::string(cstr));
}

int main()
{
    std::string s = "manbearpig";
    std::string *sp = &s;
    
    std::cout << debug_rep(s) << "\n\n";
    std::cout << debug_rep(sp) << "\n\n";
    
    std::cout << debug_rep("manbearpig") << "\n" << std::endl;
    
    return 0;
}

// output:
// debug_rep(const T &t)
// manbearpig
//
// debug_rep(Tp *p)
// debug_rep(const T &t)
// pointer: 0x7ff7bfeff1a8 manbearpig
//
// debug_rep(const char *cstr)
// debug_rep(const T &t)
// manbearpig
//
// Program ended with exit code: 0
