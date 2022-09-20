// Exercise 7.53:
/*
 Define your own version of Debug.
 */

#include <iostream>

class Debug {
public:
    constexpr Debug(bool b = true) : hw(b), io(b), runtime(b) {}
    constexpr Debug(bool b, bool i, bool r) : hw (b), io(i), runtime(r) {}
    
    // this line will not compile
    //'this' argument to member function 'any' has type 'const Debug', but function is not marked const
    // constexpr bool any() { return hw || io || runtime; }
    
    // to fix this, mark the any() function as explicitly "const"
    constexpr bool any() const { return hw || io || runtime; }
    
    void set_hw(bool b) { hw = b; }
    void set_io(bool b) { io = b; }
    void set_runtime(bool b) { runtime = b; }
private:
    bool hw;        // hardware errors other than IO errors
    bool io;        // IO errors
    bool runtime;   // other errors
};


int main() {
    // hw = false, io = true, runtime = false
    constexpr Debug io_sub(false, true, false); // debugging IO
    if (io_sub.any())
        std::cerr << "Error message 1" << std::endl;
    
    constexpr Debug prod(false);    // no debugging during production
    if (prod.any())     // equivalent to if (false)
        std::cerr << "code will never be executed" << std::endl;
    
    return 0;
}
