// Exercise 16.41:
/*
 Write a version of sum with a return type that is guaranteed to be large enough to hold the result of the addition.
*/

#include <iostream>
#include <climits>

// explicit-specified template parameter type
// can produce undesirable behaviour
template <typename T> auto sum(T t1, T t2)
{ return t1 + t2; }

// trailing return type – can also produce undesirable behaviour
template <typename T> auto sum2(T t1, T t2) -> decltype(t1 + t2)
{ return t1 + t2; }

int main()
{
    // output: 4294967294 (-2 if sum<int>)
    std::cout << sum<unsigned long long>(INT_MAX, INT_MAX) << std::endl;
    // output: -2
    std::cout << sum2(INT_MAX, INT_MAX) << std::endl;
    
    // output: 18446744073709551614
    std::cout << sum<unsigned long long>(ULLONG_MAX, ULLONG_MAX) << std::endl;
    // output: 18446744073709551614
    std::cout << sum2(ULLONG_MAX, ULLONG_MAX) << std::endl;
    
    // output: 18446744073709551612
    std::cout << sum<unsigned long long>(-2, -2) << std::endl;
    // output: -4
    std::cout << sum2(-2, -2) << std::endl;
    
    return 0;
}
