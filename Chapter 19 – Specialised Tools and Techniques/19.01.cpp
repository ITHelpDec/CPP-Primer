// Exercise 19.01:
/*
 Write your own operator new(size_t) function using malloc and use free to write the operator delete(void*) function.
 
 EDIT: kudos to "Undefined Behaviour as Gaeilge" for the help with prompts and amendments with regards to C++17
*/

#include <iostream>
#include <cstdio>
// #include <stdexcept>
#include <new>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// C++11 versions  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// allocate an element
void *operator new(std::size_t size) {
    if (void *mem = std::malloc(size)) {
        std::cout << "void *operator new(std::size_t)" << std::endl;
        return mem;
    } else {
        throw std::bad_alloc();
    }
}

// allocates an array
void *operator new[](std::size_t size) {
    // if (void *mem = (int*)std::malloc(size * sizeof(int))) {
    if (void *mem = std::malloc(size)) {
        std::cout << "void *operator new[](std::size_t)" << std::endl;
        return mem;
    } else {
        throw std::bad_alloc();
    }
}

// frees an element
void operator delete(void *mem) noexcept {
    std::cout << "void operator delete(void*) noexcept" << std::endl;
    std::free(mem);
}

// frees an array
void operator delete[](void *mem) noexcept {
    std::cout << "void operator delete[](void*) noexcept" << std::endl;
    std::free(mem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// C++11 versions with std::nothrow_t& - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// allocate an element
void *operator new(std::size_t size, std::nothrow_t &tag) noexcept {
    if (void *mem = std::malloc(size)) {
        std::cout << "void *operator new(std::size_t, std::nothrow_t&) noexcept" << std::endl;
        return mem;
    } else {
        return nullptr;
    }
}

// allocates an array
void *operator new[](std::size_t size, std::nothrow_t &tag) noexcept {
    if (void *mem = std::malloc(size)) {
        std::cout << "void *operator new[](std::size_t, std::nothrow_t&) noexcept" << std::endl;
        return mem;
    } else {
        return nullptr;
    }
}

// frees an element
void operator delete(void *mem, std::nothrow_t &tag) noexcept {
    std::cout << "void operator delete(void*, std::nothrow_t&) noexcept" << std::endl;
    std::free(mem);
}

// frees an array
void operator delete[](void *mem, std::nothrow_t &tag) noexcept {
    std::cout << "void operator delete[](void*, std::nothrow_t&) noexcept" << std::endl;
    std::free(mem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// C++17 versions  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// allocate an element
void *operator new(std::size_t size, std::align_val_t al) {
    if (void *mem = std::aligned_alloc(static_cast<std::size_t>(al), size)) {
        std::cout << "void *operator new(std::size_t, std::align_val_t)" << std::endl;
        return mem;
    } else {
        throw std::bad_alloc();
    }
}

// allocates an array
void *operator new[](std::size_t size, std::align_val_t al) {
    if (void *mem = std::aligned_alloc(static_cast<std::size_t>(al), size)) {
        std::cout << "void *operator new[](std::size_t, std::align_val_t)" << std::endl;
        return mem;
    } else {
        throw std::bad_alloc();
    }
}

// frees an element
void operator delete(void *mem, std::align_val_t al) noexcept {
    std::cout << "void operator delete(void*, std::align_val_t) noexcept" << std::endl;
    std::free(mem);
}

// frees an array
void operator delete[](void *mem, std::align_val_t al) noexcept {
    std::cout << "void operator delete[](void*, std::align_val_t) noexcept" << std::endl;
    std::free(mem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
// C++17 versions with std::no_throwt& - - - - - - - - - - - - - - - - - - - -
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// allocate an element
void *operator new(std::size_t size, std::align_val_t al, std::nothrow_t &tag) noexcept {
    if (void *mem = std::aligned_alloc(static_cast<std::size_t>(al), size)) {
        std::cout << "void *operator new(std::size_t, std::align_val_t, std::nothrow_t&) noexcept" << std::endl;
        return mem;
    } else {
        return nullptr;
    }
}

// allocates an array
void *operator new[](std::size_t size, std::align_val_t al, std::nothrow_t &tag) noexcept {
    if (void *mem = std::aligned_alloc(static_cast<std::size_t>(al), size)) {
        std::cout << "void *operator new[](std::size_t, std::align_val_t, std::nothrow_t&) noexcept" << std::endl;
        return mem;
    } else {
        return nullptr;
    }
}

// frees an element
void operator delete(void *mem, std::align_val_t al, std::nothrow_t &tag) noexcept {
    std::cout << "void operator delete(void*, std::align_val_t, std::nothrow_t&) noexcept" << std::endl;
    std::free(mem);
}

// frees an array
void operator delete[](void *mem, std::align_val_t al, std::nothrow_t &tag) noexcept {
    std::cout << "void operator delete[](void*, std::align_val_t, std::nothrow_t&) noexcept" << std::endl;
    std::free(mem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

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
