// Example 16.06:
/*
 How do you think the library begin and end functions that take an array argument work?
 Define your own versions of these functions.
*/

#include <iostream>
#include <vector>

// https://en.cppreference.com/w/cpp/iterator/begin
template <class C> constexpr auto templateFirst(const C &c) { return c.begin(); }
template <class C> constexpr auto templateLast(const C &c) { return c.end(); }

// https://en.cppreference.com/w/cpp/iterator/end
template <class T, std::size_t N> constexpr T* templateBegin(T (&arr) [N]) noexcept { return arr; }
template <class T, std::size_t N> constexpr T* templateEnd(T (&arr) [N]) noexcept { return arr + N; }

template <typename T, std::size_t N> constexpr void printArray(const T (&arr) [N]) {
    for (auto it = templateBegin(arr); it != templateEnd(arr); ++it) {
        std::cout << *it << " ";
    } std::cout << std::endl;
}

void printVec(const std::vector<int> &ivec) {
    for (auto it = templateFirst(ivec); it != templateLast(ivec); ++it) {
        std::cout << *it << " ";
    } std::cout << std::endl;
}

int main()
{
    std::vector<int> ivec = { 1, 2, 3, 4, 5 };
    std::cout<< "ivec: "; printVec(ivec);
    
    int arr[5] = { 5, 4, 3, 2, 1 };
    std::cout<< "arr:  "; printArray(arr);
    
    return 0;
}
