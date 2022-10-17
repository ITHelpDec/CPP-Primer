#include "String.hpp"

String::String() : cp(nullptr), offtheend(nullptr), cap(nullptr) { }

String::String(const char *cstr) : cp(alloc.allocate(std::strlen(cstr))), offtheend(cp + std::strlen(cstr))
{ std::uninitialized_copy(cstr, cstr + std::strlen(cstr), cp); }

String::String(std::initializer_list<char> &&il)
{ for (const auto &e : il) push_back(e); }

// copy
String::String(const String &o)
{
    cp = alloc.allocate(o.size());
    offtheend = cap = std::uninitialized_copy(o.begin(), o.end(), cp);
}

String &String::operator=(const String &rhs)
{
    auto new_cp = alloc.allocate(rhs.size());
    auto new_offtheend = std::uninitialized_copy(rhs.begin(), rhs.end(), new_cp);
  
    free();
    cp = new_cp;
    offtheend = cap = new_offtheend;
    return *this;
}

// move
String::String(String &&rhs) noexcept : cp(rhs.cp), offtheend(rhs.offtheend), cap(rhs.cap)
{ rhs.cp = rhs.offtheend = rhs.cap = nullptr; }


String &String::operator=(String &&rhs) noexcept
{
    if (this != &rhs) {
        free();
        cp = std::move(rhs.cp);
        offtheend = std::move(rhs.offtheend);
        cap = rhs.cap;
        rhs.cp = rhs.offtheend = rhs.cap = nullptr;
    }
    return *this;
}

// destroy
String::~String() { free(); }

// "[]" operators
char& String::operator[](std::size_t &n) { return cp[n]; }
const char& String::operator[](std::size_t &n) const { return cp[n]; }

void String::push_back(const char &c)
{
    if (size() == capacity())
        reallocate(empty() ? 1 : 2 * capacity());
      alloc.construct(offtheend++, c);
}

void String::pop_back()
{
    if (!empty())
        alloc.destroy(--offtheend);
}

bool String::empty() const { return !cp; }
std::size_t String::size() const { return offtheend - cp; }
std::size_t String::capacity() const { return cap - cp; }

void String::free()
{
    std::for_each(cp, offtheend, [] (char &cp) {alloc.destroy(&cp); } );
    alloc.deallocate(cp, offtheend - cp);
}

void String::reallocate(const std::size_t &n)
{
    auto new_cp = alloc.allocate(n);
    auto new_offtheend = new_cp;
    for (auto it = begin(); it != end(); ++it)
        alloc.construct(new_offtheend++, std::move(*it));
        // or...
        // new_offtheend = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), new_cp);
        //
    free();
    cp = new_cp;
    offtheend = new_offtheend;
    cap = cp + n;
}

std::ostream &operator<<(std::ostream &os, const String &S)
{
    for (const auto &c : S) os << c;
    return os;
}

bool operator==(const String &lhs, const String &rhs)
{ return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin()); }

bool operator!=(const String &lhs, const String &rhs) { !(lhs == rhs); }

bool operator<(const String &lhs, const String &rhs)
{
    auto rhs_it = rhs.begin();
    if (lhs.size() < rhs.size()) {
        for (const auto &e : lhs)
            if (!(e < *rhs_it++))
                return false;
        return true;
    }
}
bool operator>(const String &lhs, const String &rhs) { return rhs < lhs; }
bool operator<=(const String &lhs, const String &rhs) { return !(lhs > rhs); }
bool operator>=(const String &lhs, const String &rhs) { return !(lhs < rhs); }

int main()
{
    std::cout << "Creating String...";
    String S = { "manbearpig" };
    
    std::cout << "\nTraversing characters of string using subscripts...\n\"";
    for (std::size_t i = 0; i != S.size(); ++i) {
        std::cout << S[i];
    } std::cout << "\"" << std::endl;
    
    std::cout << "\nChanging each character to 'a' using subscripts...";
    for (std::size_t i = 0; i != S.size(); ++i) {
        S[i] = 'a';
    } std::cout << std::endl;
    
    std::cout << "\nTraversing through characters again...\n";
    for (std::size_t i = 0; i != S.size(); ++i) {
        std::cout << S[i] << " ";
    } std::cout << std::endl;
    
    return 0;
}
