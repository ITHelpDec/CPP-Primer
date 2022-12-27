// Exercise 18.03:
/*
 There are two ways to make the previous code work correctly if an exception is thrown.
 Describe them and implement them.
 
 >> There are two things we can do:
 >> (1) Encapsulate everything withina class (RAII)
 >> (2) Use smart pointers to assist with freeing dynamically-allocated resources
 
*/

#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <memory>

struct tempArray {
    tempArray(std::size_t sz)
    {
        p = new int[sz];
    }
    
    ~tempArray()
    {
        delete[] p;
        p = nullptr;
    }
    
    int *p = nullptr;
};

// function takes begin() and end() iterators
void exercise(int *b, int *e) {
    std::vector<int> ivec(b, e);
    
    // int *p = new int[ivec.size()];
    
    // we could opt for a unique_ptr, so that the class calls it destructor to free the resource
    // up.release() will call delete[] p
    auto up = std::make_unique<int[]>(ivec.size());
    
    // from C++20 we could use std::make_shared<_T[]>
    // auto sp20 = std::make_shared<int[]>(ivec.size());

    // before C++20, we would need to supply our own deleter as part of the initialisation
    // sp.reset() will help call our lambda delete[]
    std::shared_ptr<int[]> sp(new int[ivec.size()], [] (int p[]) { delete[] p; p = nullptr; });
    
    // we could also opt for std::array, or encapsulate everything within a separate class / struct (RAII)
    // ~tempArray() will free the dynamically-allocated array's memory and leave it in a stable state
    tempArray temp(ivec.size());
    
    std::ifstream file("ints");
    
    // exception occurs here
    
    throw std::exception();
    // begin unwinding the stack and terminate if not throw not caught
    //
    // libc++abi: terminating with uncaught exception of type std::exception: std::exception
    // terminating with uncaught exception of type std::exception: std::exception
}

int main()
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    
    // exercise(arr, arr + sizeof(arr) / sizeof(*arr));
    exercise(arr, std::end(arr));
    
    return 0;
}

