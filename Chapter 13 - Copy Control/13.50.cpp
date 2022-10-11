// Exercise 13.50:
/*
 Put print statements in the move operations in your String class and rerun the program from exercise 13.48 in § 13.6.1 (p. 534) that used a vector<String> to see when the copies are avoided
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
    ori.cp = ori.offtheend = nullptr;
    
    // print funciton to show when copy constructor has been avoided
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
        rhs.cp = rhs.offtheend = nullptr;
        
        // print funciton to show when copy-assignment has been avoided
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
    std::vector<String> Svec;
    Svec.push_back("man");          // 1 calls
    Svec.push_back("bear");         // 3 calls
    Svec.push_back("pig");          // 6 calls
    Svec.push_back("youguys");      // 7 calls
    Svec.push_back("youguys");      // 12 calls
    Svec.push_back("woof");         // 13 calls
    
    return 0;
}
