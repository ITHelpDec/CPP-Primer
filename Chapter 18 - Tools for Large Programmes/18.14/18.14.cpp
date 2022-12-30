// Exercise 18.14:
/*
 Suppose we have the following declaration of the operator* that is
 a member of the nested namespace mathLib::MatrixLib:
 
 How would you declare this operator in global scope?
 
 >> This is a great opportunity to benchmark loop interchanging
 >> Surprisingly, there were no differences on my machine!
 
*/

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
    
    long long average1 = 0;
    for (int i = 0; i != 100; ++i) {
        average1 += benchmark_non_inter(10000);
        average1 >>= 1;
        if (i == 50) { std::cout << "\n>>> "; }
        if (!(i % 10)) { std::cout << average1 << "µs... "; }
    }
    
    std::cout << "\naverage: " << average1 << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "interlooping:...\n>>> ";
    
    long long average2 = 0;
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
