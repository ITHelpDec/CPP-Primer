// String

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
    
    // move constructor and move-assignment oeprator
    String(String&&) noexcept;
    String& operator=(String&&) noexcept;
    
    void free();
    std::size_t size() { return offtheend - cp; }
    
    char *begin() const { return cp; }
    char *end() const { return offtheend; }
    
private:
    static std::allocator<char> alloc;
    char *cp = nullptr;
    char *offtheend = nullptr;
    
    std::pair<char*, char*> alloc_n_cpy(const char*, const char*);
    
    // another utility function to help with allocation and movement
    std::pair<char*, char*> alloc_n_move(char*, char*);
};

std::allocator<char> String::alloc;

void String::free()
{
    std::for_each(cp, offtheend, [] (char &cp) {alloc.destroy(&cp); } );
    alloc.deallocate(cp, offtheend - cp);
}

String::~String()
{
    free();
}

String::String(const String &ori)
{
    auto ori_data = alloc_n_cpy(ori.begin(), ori.end());
    cp = ori_data.first;
    offtheend = ori_data.second;
    std::cout << "(Copy contructor called)" << std::endl;
}

// move constructor
String::String(String &&ori) noexcept
{
    auto ori_data = alloc_n_move(ori.begin(), ori.end());
    cp = std::move(ori_data.first);
    offtheend = std::move(ori_data.second);
    
    // MAKE SURE TO LEAVE rhs MEMBERS DESTRUCTABLE
    ori.cp = ori.offtheend = nullptr;
    
    std::cout << "Move constructor called)" << std::endl;
}

std::pair<char*, char*> String::alloc_n_cpy(const char *b, const char* e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(b, e, data) };
}

// utility helper function
std::pair<char*, char*> String::alloc_n_move(char *b, char* e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(std::make_move_iterator(b), std::make_move_iterator(e), data) };
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

// move-assignment operator
String& String::operator=(String &&rhs) noexcept
{
    if (this != &rhs) {
        auto rhsdata = alloc_n_move(rhs.begin(), rhs.end());
        free();
        cp = std::move(rhsdata.first);
        offtheend = std::move(rhsdata.second);
        
        // MAKE SURE TO LEAVE rhs MEMBERS DESTRUCTABLE
        rhs.cp = rhs.offtheend = nullptr;
        
        std::cout << "(Move assignment operator caled)" << std::endl;
    }
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
    std::cout << "Creating two Strings...\n";
    String s1 = "totally";
    String s2("cereal");
    
    std::cout << "Printing results...\n";
    cprint(s1);
    cprint(s2);
    
    std::cout << "\nMoving contents of s1 into new String...\n";
    String s3 = std::move(s1);
    cprint(s3);
    
    std::cout << "\nMove-assigning contents of s2 into yet another new String...\n";
    String s4;
    s4 = std::move(s2);
    cprint(s4);
    
    return 0;
}
