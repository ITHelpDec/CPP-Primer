// Exercise 16.52:
/*
 Write a program to check your answer to the previous question.
*/

#include <iostream>
#include <string>

template <typename T, typename ...Args> void foo(const T &t, const Args& ...rest) { std::cout << "This is a variadic template with " << sizeof...(Args)
    << " template " << (sizeof...(Args) == 1 ? "argument" : "arguments")
    << " and " << sizeof...(rest) << " function "
    << (sizeof...(rest) == 1 ? "argument." : "arguments.") << std::endl;
    
}

int main()
{
    int i = 0;
    double d = 3.14;
    std::string s = "manbearpig";
    
    // void foo(const int&, const std::string&, const int&, const double&);
    //
    // sizeof...(Args)  == 3;   sizeof...(rest) == 3
    // total types      == 3;   total arguments == 4
    std::cout << "foo(i, s, 42, d)" << std::endl;
    foo(i, s, 42, d);
    
    // void foo(const std::string&, const int&, const char(&)[3]);
    // { 'h', 'i', '\0' }
    //
    // sizeof...(Args)  == 2;   sizeof...(rest) == 2
    // total types      == 3;   total arguments == 3
    std::cout << "\nfoo(s, 42, \"hi\")" << std::endl;
    foo(s, 42, "hi");
    
    // void foo(const double&, const std::string&);
    //
    // sizeof...(Args)  == 1;   sizeof...(rest) == 1
    // total types      == 2;   total arguments == 2
    std::cout << "\nfoo(d, s)" << std::endl;
    foo(d, s);
    
    // void foo(const char(&)[3]);
    // { 'h', 'i', '\0' }
    //
    // sizeof...(Args)  == 0;   sizeof...(rest) == 0
    // total types      == 1;   total arguments == 1
    std::cout << "\nfoo(\"hi\")" << std::endl;
    foo("hi");
    
    return 0;
}

// output:
// foo(i, s, 42, d)
// This is a variadic template with 3 template arguments and 3 function arguments.
//
// foo(s, 42, "hi")
// This is a variadic template with 2 template arguments and 2 function arguments.
//
// foo(d, s)
// This is a variadic template with 1 template argument and 1 function argument.
//
// foo("hi")
// This is a variadic template with 0 template arguments and 0 function arguments.
// Program ended with exit code: 0
