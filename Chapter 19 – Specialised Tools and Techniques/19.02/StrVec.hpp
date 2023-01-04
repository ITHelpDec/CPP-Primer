// Exercise 19.02:
/*
By default, the allocator class uses operator new to obtain storage and operator delete to free it.
Recompile and rerun your StrVec programs (§ 13.5, p. 526) using your versions of the functions from the previous exercise.
*/

#ifndef StrVec_hpp
#define StrVec_hpp

#include <initializer_list>
#include <string>
#include <iostream>
// #include <cstdlib>
// #include <memory>
// #include <utility>
// #include <iterator>
// #include <algorithm>

class StrVec {
    friend bool operator==(const StrVec&, const StrVec&);
    friend bool operator!=(const StrVec&, const StrVec&);
    
    friend bool operator< (const StrVec&, const StrVec&);
    friend bool operator> (const StrVec&, const StrVec&);
    friend bool operator<=(const StrVec&, const StrVec&);
    friend bool operator>=(const StrVec&, const StrVec&);
public:
    // constructors
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string>&&) noexcept;
    
    // copy and copy-assignment
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    
    // move and move-assignment
    StrVec(StrVec&&) noexcept;
    StrVec& operator=(StrVec&&) noexcept;
    StrVec& operator=(std::initializer_list<std::string>&&) noexcept;
    
    ~StrVec();
    
    std::string& operator[](std::size_t n)              { return elements[n]; }
    const std::string& operator[](std::size_t n) const  { return elements[n]; }
    
    void push_back(const std::string&);
    void push_back(std::string&&) noexcept;
    
    // variadic emplace_back (constexpr reference since C++20)
    template <class ...Args> constexpr void emplace_back(Args&&...);
    
    void reserve(std::size_t);
    
    void resize(const int&);
    void resize(const int&, const std::string&);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // *operator new and operator delete from previous exercise  - - - - - - -
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    void* operator new(std::size_t size) {
        if (void *mem = std::malloc(size)) {
            std::cout << "void *operator new(std::size_t)" << std::endl;
            return mem;
        } else {
            throw std::bad_alloc();
        }
    }
    
    void* operator new[](std::size_t size) {
        if (void *mem = std::malloc(size)) {
            std::cout << "void *operator new[](std::size_t)" << std::endl;
            return mem;
        } else {
            throw std::bad_alloc();
        }
    }
    
    void operator delete(void *mem) noexcept {
        std::cout << "void operator delete(void*) noexcept" << std::endl;
        std::free(mem);
    }
    
    void operator delete[](void *mem) noexcept {
        std::cout << "void operator delete[](void*) noexcept" << std::endl;
        std::free(mem);
    }
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::size_t size() const        { return first_free - elements; }
    std::size_t capacity() const    { return cap - elements; }
    
    std::string *begin() const      { return elements; }
    std::string *end() const        { return first_free; }
    
private:
    static std::allocator<std::string> alloc;
    
    std::pair<std::string*, std::string*> alloc_n_cpy(const std::string*, const std::string*);
    std::pair<std::string*, std::string*> alloc_n_move(const std::string*, const std::string*);
    
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    
    void free();
    void reallocate();
    
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

inline StrVec::StrVec(std::initializer_list<std::string> &&il) noexcept
{
    auto data = alloc_n_move(il.begin(), il.end());
    elements = std::move(data.first);
    first_free = cap = std::move(data.second);
}

inline StrVec::StrVec(const StrVec &svec)
{
    auto newdata = alloc_n_cpy(svec.begin(), svec.end());
    free();
    elements = newdata.first;
    first_free = cap = newdata.second;
}

inline StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto rhsdata = alloc_n_cpy(rhs.begin(), rhs.end());
    free();
    elements = rhsdata.first;
    first_free = cap = rhsdata.second;
    return *this;
}

inline StrVec::StrVec(StrVec &&svec) noexcept
{
    auto newdata = alloc_n_move(svec.begin(), svec.end());
    elements = std::move(newdata.first);
    first_free = cap = std::move(newdata.second);
    svec.elements = svec.first_free = svec.cap = nullptr;
}

inline StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
    if (this != &rhs) {
        auto rhsdata = alloc_n_move(rhs.begin(), rhs.end());
        elements = std::move(rhsdata.first);
        first_free = cap = std::move(rhsdata.second);
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

inline StrVec& StrVec::operator=(std::initializer_list<std::string> &&il) noexcept
{
    auto data = alloc_n_move(il.begin(), il.end());
    elements = std::move(data.first);
    first_free = cap = std::move(data.second);
    return *this;
}

inline StrVec::~StrVec()
{
    free();
}

inline void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

inline void StrVec::push_back(std::string &&s) noexcept
{
    chk_n_alloc();
    alloc.construct(first_free++, std::move(s));
}

// variadic emplace_back (constexpr reference since C++20)
template <class ...Args> inline constexpr void StrVec::emplace_back(Args &&...rest) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(rest)...);
}

inline void StrVec::reserve(std::size_t n)
{
    if (n < 0) {
        std::cerr << "Cannot reserve a negative value." << std::endl;
        return;
    }
    
    if (!(n > capacity())) {
        std::cerr << "Cannot reduce capacity any lower than current capacity of " << cap  << "." << std::endl;
        return;
    }
    
    alloc.allocate(n);
    cap = elements + n;
}

inline void StrVec::resize(const int &n)
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
    
    if (n < 0) {
        std::cerr << "Cannot have a negative size." << std::endl;
        return;
    } std::cerr << "StrVec already of size " << n << std::endl;
}

inline void StrVec::resize(const int &n, const std::string &s)
{
    if (n > size()) {
        while (n != size())
            push_back(s);
    } else {
        std::cerr << "Must enter a number greater than current size.\n" << std::endl;
    }
}

inline std::allocator<std::string> StrVec::alloc;

inline std::pair<std::string*, std::string*> StrVec::alloc_n_cpy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(b, e, data) };
}

inline std::pair<std::string*, std::string*> StrVec::alloc_n_move(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(std::make_move_iterator(b), std::make_move_iterator(e), data) };
}

inline void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements; /*...*/ )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

inline void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

inline void printVec(const StrVec &svec)
{
    std::cout << "\nPrinting vector...\n";
    for (const auto &e : svec) {
        std::cout << e;
    } std::cout << std::endl;
}

bool operator==(const StrVec &lhs, const StrVec &rhs)
{
    return (lhs.size() == rhs.size()) &&
    std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const StrVec &lhs, const StrVec &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(const StrVec &lhs, const StrVec &rhs)
{
    return rhs < lhs;
}

bool operator<=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const StrVec &lhs, const StrVec &rhs)
{
    return !(lhs < rhs);
}

#endif  /* StrVec_hpp */
