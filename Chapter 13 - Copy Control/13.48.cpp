// Exercise 13.48:
/*
 Define a vector<String> and call push_back several times on that vector.
 Run your program and see how often Strings are copied.
*/

#include <iostream>
#include <memory>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

class String {
public:
    String() = default;
    
    String(const char *cstr) : cp(alloc.allocate(std::strlen(cstr))), offtheend(cp + std::strlen(cstr))
    {
        std::uninitialized_copy(cstr, cstr + std::strlen(cstr), cp);
    }
    
    String(const String&);
    String& operator=(const String&);
    ~String();
    
    void free();
    std::size_t size() { return offtheend - cp; }
    
    char *begin() const { return cp; }
    char *end() const { return offtheend; }
    
private:
    static std::allocator<char> alloc;
    char *cp = nullptr;
    char *offtheend = nullptr;
    
    std::pair<char*, char*> alloc_n_cpy(const char*, const char*);
};

std::allocator<char> String::alloc;

void String::free()
{
    std::for_each(cp, offtheend, [] (char &cp) {alloc.destroy(&cp); } );
    alloc.deallocate(cp, offtheend - cp);
    // std::cout << "(Destructor called.)" << std::endl;
}

// destructor
String::~String()
{
    free();
}

// copy constructor
String::String(const String &ori)
{
    auto ori_data = alloc_n_cpy(ori.begin(), ori.end());
    cp = ori_data.first;
    offtheend = ori_data.second;
    std::cout << "(Copy contructor called)" << std::endl;
}

std::pair<char*, char*> String::alloc_n_cpy(const char *b, const char* e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(b, e, data) };
}

String& String::operator=(const String &rhs)
{
    auto rhsdata = alloc_n_cpy(rhs.begin(), rhs.end());
    free();
    cp = rhsdata.first;
    offtheend = rhsdata.second;
    std::cout << "(Copy-assignment operator called)" << std::endl;
    return *this;
}

void cprint(const String &s)
{
    for (const auto &c : s) {
        std::cout << "\'" << c << "\' ";
    } std::cout << std::endl;
}

int main()
{
    std::vector<String> svec;
    
    svec.push_back("man");
    svec.push_back("bear");
    svec.push_back("pig");
    
    for (const auto &e : svec) {
        cprint(e);
    } std::cout << std::endl;
    
    std::cout << "Copy constructor is called 6 times for 3 calls push_back()." << std::endl;
    
    return 0;
}
