// Exercise 18.19:
/*
 What if the call to swap was std::swap(v1.mem1, v2.mem1)?
 
 >> If we use std::swap(v1.mem1, v2.mem1) in the code below, we achieve the same result – mem1's swap about between objects (minus the "woofs").
 
 >> However, if we had T mem2's in each struct, these would not be swapped across, unless we used the generic std::swap(v1, v2) from the previous exercise' context.
 
 >> Choose depending on the desired result.
 
*/

#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

template <typename T> struct V {
    V(T x) : mem1(x) { }
    T mem1, mem2;
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
    std::string s3 = " have", s4 = " i";
    
    V<std::string> v1 = s1, v2 = s2;
    v1.mem2 = s3, v2.mem2 = s4;
    
    std::cout << v1.mem1 << v2.mem1 << std::endl;
    std::cout << v1.mem2 << v2.mem2 << " been swapped?" << std::endl;
    
    // take your pick
    // (1)
    // std::swap(v1, v2);
    // (2)
    // ::swap(v1, v2);
    // (3)
    // std::swap(v1.mem1, v2.mem1);
    
    // swap(v1, v2);
    // error: "Call to 'swap' is ambiguous"
    
    std::cout << v1.mem1 << v2.mem1 << std::endl;
    std::cout << v1.mem2 << v2.mem2 << " been swapped?" << std::endl;
}

void intV()
{
    V<int> v1 = 4, v2 = 2;
    v1.mem2 = 5, v2.mem2 = 6;
    
    std::cout << "v1.mem1: " << v1.mem1 << ", ";
    std::cout << "v1.mem2: " << v1.mem2 << ", ";
    std::cout << "v2.mem1: " << v2.mem1 << ", ";
    std::cout << "v2.mem1: " << v2.mem2 << std::endl;
    
    // take your pick
    // (1)
    // swap(v1, v2);
    // (2)
    // std::swap(v1, v2);
    // (3)
    // std::swap(v1.mem1, v2.mem1);
    
    std::cout << "v1.mem1: " << v1.mem1 << ", ";
    std::cout << "v1.mem2: " << v1.mem2 << ", ";
    std::cout << "v2.mem1: " << v2.mem1 << ", ";
    std::cout << "v2.mem1: " << v2.mem2 << std::endl;
}

int main()
{
    stringV();
    
    std::cout << "\n";
    
    intV();
}
