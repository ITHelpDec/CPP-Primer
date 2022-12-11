// Exercise 16.45:
/*
 Given the following template, explain what happens if we call g on a literal value such as 42.
 What if we call g on a variable of type int?
*/

#include <vector>
#include <iostream>

template <typename T> void printVec(const std::vector<T> &tvec) {
    for (const auto &t : tvec) {
        std::cout << t << " ";
    } std::cout << std::endl;
}

template <typename T> void g(T&& val) {
    std::vector<T> v(3, val);
    printVec(v);
}

int main()
{
    // argument is an rvalue; T is deduced as int&&
    // val == int&& && == int&&
    // std::vector<T> will become std::vector<int>
    // std::vector<int> is LEGAL
    g(42);
    
    int i = 3;
    // g(i);
    // argument is an lvalue; T is deduced as int&
    // val == int& && == int&
    // std::vector<T> -> std::vector<int&>
    // std::vector<int&> is NOT LEGAL
    
    return 0;
}
