// Exercise 19.01:
/*
 Write your own operator new(size_t) function using malloc and use free to write the operator delete(void*) function.
*/

#include <iostream>
#include <cstdio>
#include <stdexcept>

// allocate an object
void *operator new(std::size_t size) {
    if (void *mem = std::malloc(size)) {
        std::cout << "Element successfully allocated." << std::endl;
        return mem;
    }
    else
        throw std::bad_alloc();
}

// allocates an array
void *operator new[](std::size_t size) {
    if (void *mem = (void*)std::malloc(size * sizeof(void*))) {
        std::cout << "Array successfully allocated." << std::endl;
        return mem;
    }
    else
        throw std::bad_alloc();
}

// frees an element
void operator delete(void *mem) noexcept {
    std::cout << "Element memory freed." << std::endl;
    std::free(mem);
}

// frees an array
void operator delete[](void *mem) noexcept {
    std::cout << "Array memory freed." << std::endl;
    std::free(mem);
}

int main()
{
    int *ip;// = nullptr;
    std::cout << "ip: " << ip
              << " (" << sizeof(ip) <<  " bytes)\n"
              << "value: " << *ip
              << "\n" << std::endl;
    // dereferencing a nullptr will throw an exception
    
    ip = new int(69);
    std::cout << "ip: " << ip
              << " (" << sizeof(ip) <<  " bytes)\n"
              << "value: " << *ip
              << "\n" << std::endl;
    
    delete ip;
    std::cout << "ip: " << ip
              << " (" << sizeof(ip) <<  " bytes)\n"
              << "value: " << *ip
              << "\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    int *ap;// = nullptr;
    std::cout << "ap: " << ap
              << " (" << sizeof(ap) <<  " bytes)\n"
              << "value: " << ap[0] << ", " << ap[1] << ", " << ap[2]
              << "\n" << std::endl;
    // dereferencing a nullptr will throw an exception
    
    ap = new int[3];
    std::cout << "ap: " << ap
              << " (" << sizeof(ap) <<  " bytes)\n"
              << "value: " << ap[0] << ", " << ap[1] << ", " << ap[2]
              << "\n" << std::endl;
    
    delete[] ap;
    std::cout << "ap: " << ap
              << " (" << sizeof(ap) <<  " bytes)\n"
              << "value: " << ap[0] << ", " << ap[1] << ", " << ap[2]
              << "\n" << std::endl;
    
    return 0;
}
