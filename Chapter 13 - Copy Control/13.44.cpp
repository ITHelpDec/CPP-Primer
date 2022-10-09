// Exercise 13.44:
/*
 Write a class named String that is a simplified version of the library string class.
 Your class should have at least a default constructor and a constructor that takes a pointer to a C-style string.
 Use an allocator to allocate memory that your String class uses.
 
 >> Other functions declared in source code examples, but this will do for now
*/

#include <iostream>
#include <memory>
#include <cstring>
#include <algorithm>
#include <utility>

class String {
public:
    // default constructor
    String() = default;
    
    // direction taken from source files
    // (1) allocate size based on length of string
    // (2) create and offtheend position like StrVec
    // (2) populate an uninitialized_copy in this range using the contents of cp
    String(const char *cstr) : cp(alloc.allocate(std::strlen(cstr))), offtheend(cp + std::strlen(cstr))
    {
        std::uninitialized_copy(cstr, cstr + std::strlen(cstr), cp);
    }
    
    // copy constructor
    String(const String&);
    String& operator=(const String&);
    ~String();
    
    void free();
    std::size_t size() { return offtheend - cp; }
    
    char *begin() const { return cp; }
    char *end() const { return offtheend; }
    
private:
    static std::allocator<char> alloc;
    // char *cstring;
    char *cp = nullptr;
    char *offtheend = nullptr;
    
    std::pair<char*, char*> alloc_n_cpy(const char*, const char*);
};

std::allocator<char> String::alloc;

void String::free()
{
    // destroy then deallocate
    std::for_each(cp, offtheend, [] (char &cp) {alloc.destroy(&cp); } );
    alloc.deallocate(cp, offtheend - cp);
    // std::cout << "(Successful destruction.)" << std::endl;
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
    std::cout << "Creating String...\n";
    String s1("manbearpig");
    std::cout << "Printing contents: ";
    cprint(s1);
    std::cout << "Our String has " << s1.size() << (s1.size() == 1 ? " character." : " characters.") << std::endl;
    
    std::cout << "\nCreating an empty String...\n";
    String s2;
    std::cout << "Setting new String to first string...\n";
    s2 = s1;
    std::cout << "Printing contents: ";
    cprint(s2);
    std::cout << "Our new String has " << s2.size() << (s2.size() == 1 ? " character." : " characters.") << std::endl;
    
    std::cout << "\nCreating another String equal to our first String...\n";
    String s3 = s1;
    std::cout << "Printing contents: ";
    cprint(s3);
    std::cout << "Our final String has " << s3.size() << (s3.size() == 1 ? " character." : " characters.") << std::endl;
    
    return 0;
}
