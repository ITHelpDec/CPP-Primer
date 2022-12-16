// Exercise 16.51:
/*
 Determine what sizeof...(Args) and sizeof...(rest) return for each call to foo in this section.
*/

#include <iostream>
#include <string>

template <typename T, typename ...Args> void foo(const T &t, const Args& ...rest) { }

int main()
{
    int i = 0;
    double d = 3.14;
    std::string s = "manbearpig";
    
    // void foo(const int&, const std::string&, const int&, const double&);
    //
    // sizeof...(Args)  == 3;   sizeof...(rest) == 3
    // total types      == 3;   total arguments == 4
    foo(i, s, 42, d);
    
    // void foo(const std::string&, const int&, const char(&)[3]);
    // { 'h', 'i', '\0' }
    //
    // sizeof...(Args)  == 2;   sizeof...(rest) == 2
    // total types      == 3;   total arguments == 3
    foo(s, 42, "hi");
    
    // void foo(const double&, const std::string&);
    //
    // sizeof...(Args)  == 1;   sizeof...(rest) == 1
    // total types      == 2;   total arguments == 2
    foo(d, s);
    
    // void foo(const char(&)[3]);
    // { 'h', 'i', '\0' }
    //
    // sizeof...(Args)  == 0;   sizeof...(rest) == 0
    // total types      == 1;   total arguments == 1
    foo("hi");
    
    return 0;
}
