// Exercise 18.18:
/*
 Given the following typical definition of swap § 13.3 (p. 517), determine which version of swap is used if mem1 is a string.
 What if mem1 is an int?
 Explain how name lookup works in both cases.
*/

#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

template <typename T> struct V {
    V(T x) : mem1(x) { }
    T mem1;
};

// "void swap(T v1, T v2)"
// nothing actually swaps unless we call by reference...
template <class T> void swap(T &v1, T &v2) {
    using std::swap;
    std::cout << "woof" << std::endl;
    swap(v1.mem1, v2.mem1);
}

void stringV()
{
    std::string s1 = " nice", s2 = " to see you,";
    V<std::string> v1 = s1, v2 = s2;
    
    std::cout << v1.mem1 << v2.mem1 << std::endl;
    
    ::swap(v1, v2);
    // error: "Call to 'swap' is ambiguous"
    // ::swap works; as does std::swap
    
    std::cout << v1.mem1 << v2.mem1 << std::endl;
}

void intV()
{
    V<int> v1 = 4, v2 = 2;
    
    std::cout << "v1.mem1: " << v1.mem1 << ", ";
    std::cout << "v2.mem1: " << v2.mem1 << std::endl;
    
    swap(v1, v2);
    // function swap called
    // std::swap can also be called
    
    std::cout << "v1.mem1: " << v1.mem1 << ", ";
    std::cout << "v2.mem1: " << v2.mem1 << std::endl;
}

int main()
{
    stringV();
    
    std::cout << "\n";
    
    intV();
    
    return 0;
}
