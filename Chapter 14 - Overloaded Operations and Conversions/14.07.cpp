// Exercise 14.07
/*
 Define an output operator for you String class you wrote for the exercises in § 13.5 (p. 531).
*/

#include <iostream>
#include <initializer_list>
#include <memory>

class String {
    friend std::ostream &operator<<(std::ostream&, const String&);
public:
    String(const char *cstr) : cp(alloc.allocate(std::strlen(cstr))), offtheend(cp + std::strlen(cstr))
    { std::uninitialized_copy(cstr, cstr + std::strlen(cstr), cp); }
    
    ~String();
    
    void free();
    std::size_t size() { return offtheend - cp; }
    
    char *begin() const { return cp; }
    char *end() const { return offtheend; }
private:
    static std::allocator<char> alloc;
    char *cp = nullptr;
    char *offtheend = nullptr;
    
};

void String::free()
{
    std::for_each(cp, offtheend, [] (char &cp) {alloc.destroy(&cp); } );
    alloc.deallocate(cp, offtheend - cp);
}

String::~String()
{
    free();
}

std::ostream &operator<<(std::ostream &os, const String &S)
{
    for (const auto &c : S)
        os << c;
    return os;
}

int main()
{
    String S = "hello";
    
    std::cout << S << std::endl;
    
    return 0;
}
