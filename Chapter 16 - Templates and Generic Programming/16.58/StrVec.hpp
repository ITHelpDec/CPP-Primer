// Exercise 16.58:
/*
 Write the emplace_back function for your StrVec class and for the Vec class that you wrote for the exercises in § 16.1.2 (p. 668).
 
 >> lines 46 and 201
*/

#ifndef StrVec_hpp
#define StrVec_hpp

#include <memory>
#include <string>
#include <initializer_list>
#include <iostream>

class StrVec {
    friend std::ostream& operator<<(std::ostream&, const StrVec&);
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    friend bool operator<(const StrVec&, const StrVec&);
    friend bool operator>(const StrVec&, const StrVec&);
    friend bool operator<=(const StrVec&, const StrVec&);
    friend bool operator>=(const StrVec&, const StrVec&);
    
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string> il) { for (auto &s : il) push_back(s); }
    
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    
    ~StrVec();
    
    StrVec(StrVec&&) noexcept;
    StrVec& operator=(StrVec&&) noexcept;
    StrVec& operator=(std::initializer_list<std::string>&&);
    
    std::string& operator[](std::size_t n) { return elements[n]; }
    const std::string& operator[](std::size_t n) const { return elements[n]; }
    
    void push_back(const std::string&);
    void reserve(const int&);
    void resize(const int&);
    void resize(const int&, const std::string&);
    
    // variadic emplace_back (constexpr reference since C++20)
    template <class ...Args> constexpr void emplace_back(Args&&...);
    
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    
private:
    static std::allocator<std::string> alloc;
    
    std::pair<std::string*, std::string*> alloc_n_cpy(const std::string*, const std::string*);
    std::pair<std::string*, std::string*> alloc_n_move(std::string*, std::string*);
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    
    void free();
    void reallocate();
    
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string*, std::string*> StrVec::alloc_n_cpy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e-b);
    return { data, std::uninitialized_copy(b, e, data) };
}

std::pair<std::string*, std::string*> StrVec::alloc_n_move(std::string *b, std::string *e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(std::make_move_iterator(b), std::make_move_iterator(e), data) };
}

void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements;  )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

StrVec::StrVec(const StrVec &sv)
{
    auto newdata = alloc_n_cpy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::StrVec(StrVec &&sv) noexcept
{
    auto newdata = alloc_n_move(sv.begin(), sv.end());
    elements = std::move(newdata.first);
    first_free = cap = std::move(newdata.second);
    sv.elements = sv.first_free = sv.cap = nullptr;
}

StrVec::~StrVec() { free(); }

StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto rhsdata = alloc_n_cpy(rhs.begin(), rhs.end());
    free();
    
    elements = rhsdata.first;
    first_free = cap = rhsdata.second;
    
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs) {
        auto rhsdata = alloc_n_move(rhs.begin(), rhs.end());
        free();
        elements = std::move(rhsdata.first);
        first_free = cap = std::move(rhsdata.second);
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

StrVec& StrVec::operator=(std::initializer_list<std::string> &&il)
{
    auto data = alloc_n_cpy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

std::ostream& operator<<(std::ostream &os, const StrVec &svec)
{
    for (const auto &e : svec)
        os << e << " ";
    return os;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

void StrVec::reserve(const int &n)
{
    if (n < 0) { std::cerr << "Cannot reserve a negative value." << std::endl; return; }
    if (!(n > capacity())) { std::cerr << "Cannot reduce capacity any lower than current capacity of " << cap  << "." << std::endl; return; }
    alloc.allocate(n);
    cap = elements + n;
}

void StrVec::resize(const int &n)
{
    if (n < size()) {
        while (size() != n && elements) {
            alloc.destroy(--first_free);
        } return;
    }
    
    if (n > size()) {
        while (size() != n) {
            push_back("");
        } return;
    }
    
    if (n < 0) { std::cerr << "Cannot have a negative size." << std::endl; return; }
    std::cerr << "StrVec already of size " << n << std::endl;
}

void StrVec::resize(const int &n, const std::string &s)
{
    if (n > size()) {
        while (n != size())
            push_back(s);
    } else {
        std::cerr << "Must enter a number greater than current size.\n" << std::endl;
    }
}

// variadic emplace_back (constexpr reference since C++20)
template <class ...Args> inline constexpr void StrVec::emplace_back(Args &&...rest) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(rest)...);
}

void printVec(const StrVec &svec)
{
    std::cout << "Printing vector...\n";
    for (const auto &e : svec) {
        std::cout << "\"" << e << "\" ";
    } std::cout << std::endl;
}

bool operator==(const StrVec &lhs, const StrVec &rhs)
{
    return (lhs.size() == rhs.size()) &&
    std::equal(lhs.begin(), lhs.end(), rhs.begin());
    
    // also had a for loop, but no need to reinvent the wheel
    // auto rhs_it = rhs.begin();
    // for (const auto &e : lhs)
    //     if (e != *rhs_it++)
    //         return false;
}

bool operator!=(const StrVec &lhs, const StrVec &rhs) { return !(lhs == rhs); }

bool operator<(const StrVec &lhs, const StrVec &rhs)
{
    auto rhs_it = rhs.begin();
    for (auto &e : lhs)
        if (e < *rhs_it++)
            return true;
    return false;
}

bool operator>(const StrVec &lhs, const StrVec &rhs) { return rhs < lhs; }
bool operator<=(const StrVec &lhs, const StrVec &rhs) { return !(lhs > rhs); }
bool operator>=(const StrVec &lhs, const StrVec &rhs) { return !(lhs < rhs); }


#endif  /* StrVec_hpp */

