# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most Noteworthy Recent Submission (30/12/2022) .:.

```
Exercise 18.14:
Suppose we have the following declaration of the operator* that is
a member of the nested namespace mathLib::MatrixLib:
```
```cpp
namespace mathLib {
    namespace MatrixLib {
        class matrix { /* ... */ }
        matrix operator*(const matrix&, const matrix&);
        // ...
    }
}
```
```
How would you declare this operator in global scope?

>> This is a great opportunity to benchmark loop interchanging
>> Surprisingly, there were no differences on my machine!

Correction: on a 120x120 matrix, the improvement was nearly 2x
            on a 1200x1200 matrix, the improvement was 27x faster!!!
```
>>> non_inter.hpp
```cpp
#ifndef non_inter_hpp
#define non_inter_hpp

namespace non_interloop {
namespace mathLib {
namespace MatrixLib {
class matrix {
public:
    matrix() = default;
    
    matrix(std::size_t rows, std::size_t cols) {
        matrix_.resize(rows, std::vector<int>(cols));
    }
    
    void generate() {
        for (auto &vec : matrix_)
            std::generate(vec.begin(), vec.end(), [this] () { return gen(); } );
    }
    
    std::size_t size() { return matrix_.size(); }
    const std::size_t size() const { return matrix_.size(); }
    
    std::vector<int>& operator[](std::size_t i) { return matrix_[i]; }
    const std::vector<int>& operator[](std::size_t i) const { return matrix_[i]; }
    
    void print() {
        for (const auto &v : matrix_) {
            for (const auto &e : v) {
                std::cout << e << " ";
            } std::cout << std::endl;
        } std::cout << std::endl;
    }
    
private:
    std::vector<std::vector<int>> matrix_;
    
    std::size_t gen() {
        static std::default_random_engine e;
        static std::uniform_int_distribution u(1, 9);
        return u(e);
    }
};
}
}

using mathLib::MatrixLib::matrix;

matrix operator*(const matrix &lhs, const matrix &rhs)
{
    std::size_t n = lhs.size();
    
    matrix answer(n, n);
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t j = 0; j != n; ++j) {
            for (std::size_t k = 0; k != n; ++k) {
                answer[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    
    return answer;
}
}

#endif /* non_inter_hpp */
```
>>> inter.hpp
```cpp
#ifndef inter_hpp
#define inter_hpp

namespace interloop {
namespace mathLib {
namespace MatrixLib {
class matrix {
public:
    matrix() = default;
    
    matrix(std::size_t rows, std::size_t cols)
    {
        matrix_.resize(rows, std::vector<int>(cols));
    }
    
    void generate()
    {
        for (auto &vec : matrix_) { std::generate(vec.begin(), vec.end(), [this] () { return gen(); } ); }
    }
    
    const std::size_t size() const { return matrix_.size(); }
    std::size_t size() { return matrix_.size(); }
    
    std::vector<int>& operator[](std::size_t i) { return matrix_[i]; }
    const std::vector<int>& operator[](std::size_t i) const { return matrix_[i]; }
    
    void print() {
        for (const auto &v : matrix_) {
            for (const auto &e : v) {
                std::cout << e << " ";
            } std::cout << std::endl;
        } std::cout << std::endl;
    }
    
private:
    std::vector<std::vector<int>> matrix_;
    
    std::size_t gen() {
        static std::default_random_engine e;
        static std::uniform_int_distribution u(1, 9);
        return u(e);
    }
};
}
}

using mathLib::MatrixLib::matrix;

matrix operator*(const matrix &lhs, const matrix &rhs)
{
    std::size_t n = lhs.size();
    
    matrix answer(n, n);
    for (std::size_t i = 0; i != n; ++i) {
        for (std::size_t k = 0; k != n; ++k) {
            for (std::size_t j = 0; j != n; ++j) {
                answer[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    
    return answer;
}
}

#endif /* inter_hpp */
```
>>> main.cpp
```cpp
#include <vector>
#include <iostream>
#include <random>

#include "non_inter.hpp"
#include "inter.hpp"

#include <chrono>

auto benchmark_non_inter(std::size_t n) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    result -= result;
    
    for (std::size_t i = 0; i != n; ++i) {
        t1 = std::chrono::high_resolution_clock::now();
        non_interloop::matrix m1(5, 5), m2(5, 5);
        m1.generate(); m2.generate();
        non_interloop::matrix answer = non_interloop::operator*(m1, m2);
        t2 = std::chrono::high_resolution_clock::now();
        result += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        // answer.print();
    }
    
    // std::cout << "Total time: " << result << " microseconds." << std::endl;
    
    return result;
}

auto benchmark_inter(std::size_t n) {
    auto t1 = std::chrono::high_resolution_clock::now();
    auto t2 = std::chrono::high_resolution_clock::now();
    
    auto result = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    result -= result;
    
    for (std::size_t i = 0; i != n; ++i) {
        t1 = std::chrono::high_resolution_clock::now();
        interloop::matrix m1(5, 5), m2(5, 5);
        m1.generate(); m2.generate();
        interloop::matrix answer = interloop::operator*(m1, m2);
        t2 = std::chrono::high_resolution_clock::now();
        result += std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
        // answer.print();
    }
    
    // std::cout << "Total time: " << result << " microseconds." << std::endl;
    
    return result;
}

int main()
{
    std::cout << ".:. AVERAGES .:.\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "no interlooping:...\n>>> ";
    
    auto average1 = 0;
    for (int i = 0; i != 100; ++i) {
        average1 += benchmark_non_inter(10000);
        average1 >>= 1;
        if (i == 50) { std::cout << "\n>>> "; }
        if (!(i % 10)) { std::cout << average1 << "µs... "; }
    }
    
    std::cout << "\naverage: " << average1 << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "interlooping:...\n>>> ";
    
    auto average2 = 0;
    for (int i = 0; i != 100; ++i) {
        average2 += benchmark_inter(10000);
        average2 >>= 1;
        if (i == 50) { std::cout << "\n>>> "; }
        if (!(i % 10)) { std::cout << average2 << "µs... "; }
    }
    
    std::cout << "\naverage: " << average2 << "\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}
```
```
output:
.:. AVERAGES .:.

no interlooping:...
>>> 10390µs... 21447µs... 21567µs... 20384µs... 20413µs... 
>>> 20638µs... 20762µs... 20448µs... 20762µs... 20626µs... 
average: 20486

interlooping:...
>>> 12556µs... 22281µs... 22365µs... 20346µs... 21251µs... 
>>> 20562µs... 21016µs... 22811µs... 20970µs... 21574µs... 
average: 20603

Program ended with exit code: 0
```
