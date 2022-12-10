// Exercise 16.36:
/*
 What happens in the following calls:
*/

// the following code needs return types and proper brackets...
// template <typename T> f1(T, T);
// template <typename T1, typename T2) f2(T1, T2);

#include <iostream>
#include <string>

std::string typeFinder(int*) { return "int*"; }
std::string typeFinder(const int*) { return "const int*"; }
// helpful debug technique picked up from link below
// https://stackoverflow.com/questions/57053970/how-to-receive-a-function-parameter-of-any-type-in-c-and-get-the-type-of-the-p

template <typename T> void f1(T t1, T t2)
{ std::cout << "f1(" << typeFinder(t1) << ", " << typeFinder(t2) << ")" << std::endl; }

template <typename T1, typename T2> void f2(T1 t1, T2 t2)
{ std::cout << "f2(" << typeFinder(t1) << ", " << typeFinder(t2) << ")" << std::endl; }

int main()
{
    int i = 0, j = 42, *p1 = &i, *p2 = &j;
    
    const int *cp1 = &i, *cp2 = &j;
    
    // (a) fine
    std::cout << "(a): "; f1(p1, p2);
    
    // (b) fine
    std::cout << "(b): "; f2(p1, p2);
    
    // (c) fine
    std::cout << "(c): "; f1(cp1, cp2);
    
    // (d) fine
    std::cout << "(d): "; f2(cp1, cp2);
    
    // (e) – no matching call for f1(int*, const int*)
    // cannot compare T1 and T2
    // std::cout << "(e): "; f1(p1, cp1);
    
    // (e) fine, although meant to be (f)
    std::cout << "(f): "; f2(p1, cp1);
    
    return 0;
}

// output:
// (a): f1(int*, int*)
// (b): f2(int*, int*)
// (c): f1(const int*, const int*)
// (d): f2(const int*, const int*)
// (f): f2(int*, const int*)
// Program ended with exit code: 0
