// Exercise 16.34:
/*
 Given only the following code, explain whether each of these calls is
 legal.
 If so, what is the type of T? If not, why not?

*/

#include <string>

template <class T> int compare(const T&, const T&);

int main()
{
    // (a) – compare(const std::string&, const std::string&);
    // strings are of different length, therefore will not compile
    // (similar to arr[10] vs arr[42] example)
    compare("hi", "world");
    
    // (b) – compare(const std::string&, const std::string&);
    // strings are of equal length, therefore will compile
    compare("bye", "dad");
    
    // the following however would work in the case of uneven strings
    // I believe it works because s1 and s2 would act as const lvalue references (pointers), rather than const rvalue references
    std::string s1 = "hi", s2 = "world";
    compare(s1, s2);
    
    return 0;
}
