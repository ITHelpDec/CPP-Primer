// Exercise 16.58:
/*
 Write the emplace_back function for your StrVec class and for the Vec class that you wrote for the exercises in § 16.1.2 (p. 668).
 
 >> lines 60 and 214
*/

#ifndef Vec_h
#define Vec_h

#include <iostream>
#include <memory>
#include <string>
#include <initializer_list>
#include <utility>

template <typename> class Vec;

template <typename T> std::ostream& operator<<(std::ostream&, const Vec<T>&);
template <typename T> bool operator==(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator!=(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator<(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator>(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator<=(const Vec<T>&, const Vec<T>&);
template <typename T> bool operator>=(const Vec<T>&, const Vec<T>&);

template <typename T> class Vec {
    friend std::ostream& operator<< <T>(std::ostream&, const Vec<T>&);
    friend bool operator==<T>(const Vec<T>&, const Vec<T>&);
    friend bool operator!=<T>(const Vec<T>&, const Vec<T>&);
    friend bool operator< <T>(const Vec<T>&, const Vec<T>&);
    friend bool operator> <T>(const Vec<T>&, const Vec<T>&);
    friend bool operator<=<T>(const Vec<T>&, const Vec<T>&);
    friend bool operator>=<T>(const Vec<T>&, const Vec<T>&);
    
public:
    Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    Vec(std::initializer_list<T> il) : Vec()
    {
        for (auto &t : il) { push_back(t); }
    }
    
    Vec(const Vec<T>&);
    Vec<T>& operator=(const Vec<T>&);
    
    Vec(Vec<T>&&) noexcept;
    Vec<T>& operator=(Vec<T>&&) noexcept;
    Vec<T>& operator=(std::initializer_list<T>&&);
    
    ~Vec<T>();
    
    T& operator[](std::size_t n) { return elements[n]; }
    const T& operator[](std::size_t n) const { return elements[n]; }
    
    void push_back(const T&);
    void reserve(const int&);
    void resize(const int&);
    void resize(const int&, const T&);
    
    // variadic emplace_back (constexpr reference since C++20)
    template <class ...Args> constexpr void emplace_back(Args&&...);
    
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    T *begin() const { return elements; }
    T *end() const { return first_free; }
    
private:
    static std::allocator<T> alloc;
    
    std::pair<T*, T*> alloc_n_cpy(const T*, const T*);
    std::pair<T*, T*> alloc_n_move(T*, T*);
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    
    void free();
    void reallocate();
    
    T *elements;
    T *first_free;
    T *cap;
};

template <typename T> inline std::allocator<T> Vec<T>::alloc;

template <typename T> inline void Vec<T>::push_back(const T &t)
{
    chk_n_alloc();
    alloc.construct(first_free++, t);
}

template <typename T> inline std::pair<T*, T*> Vec<T>::alloc_n_cpy(const T *b, const T *e)
{
    auto data = alloc.allocate(e-b);
    return { data, std::uninitialized_copy(b, e, data) };
}

template <typename T> inline std::pair<T*, T*> Vec<T>::alloc_n_move(T *b, T *e)
{
    auto data = alloc.allocate(e - b);
    return { data, std::uninitialized_copy(std::make_move_iterator(b), std::make_move_iterator(e), data) };
}

template <typename T> inline void Vec<T>::free()
{
    if (elements) {
        for (auto p = first_free; p != elements;  )
            alloc.destroy(--p);
        alloc.deallocate(elements, cap - elements);
    }
}

template <typename T> inline Vec<T>::Vec(const Vec<T> &sv)
{
    auto newdata = alloc_n_cpy(sv.begin(), sv.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename T> inline Vec<T>::Vec(Vec<T> &&sv) noexcept
{
    auto newdata = alloc_n_move(sv.begin(), sv.end());
    elements = std::move(newdata.first);
    first_free = cap = std::move(newdata.second);
    sv.elements = sv.first_free = sv.cap = nullptr;
}

template <typename T> inline Vec<T>::~Vec() { free(); }

template <typename T> inline Vec<T>& Vec<T>::operator=(const Vec<T> &rhs)
{
    auto rhsdata = alloc_n_cpy(rhs.begin(), rhs.end());
    free();
    
    elements = rhsdata.first;
    first_free = cap = rhsdata.second;
    
    return *this;
}

template <typename T> inline Vec<T>& Vec<T>::operator=(Vec<T> &&rhs) noexcept
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

template <typename T> inline Vec<T>& Vec<T>::operator=(std::initializer_list<T> &&il)
{
    auto data = alloc_n_cpy(il.begin(), il.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

template <typename T> inline std::ostream& operator<<(std::ostream &os, const Vec<T> &tvec)
{
    for (const auto &t : tvec) { os << t << " "; }
    return os;
}

template <typename T> inline void Vec<T>::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = std::uninitialized_copy(std::make_move_iterator(begin()), std::make_move_iterator(end()), first);
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

template <typename T> inline void Vec<T>::reserve(const int &n)
{
    if (n < 0) { std::cerr << "Cannot reserve a negative value." << std::endl; return; }
    if (!(n > capacity())) { std::cerr << "Cannot reduce capacity any lower than current capacity of " << cap  << "." << std::endl; return; }
    alloc.allocate(n);
    cap = elements + n;
}

template <typename T> inline void Vec<T>::resize(const int &n)
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
    std::cerr << "Vec already of size " << n << std::endl;
}

template <typename T> inline void Vec<T>::resize(const int &n, const T &t)
{
    if (n > size()) {
        while (n != size())
            push_back(t);
    } else {
        std::cerr << "Must enter a number greater than current size.\n" << std::endl;
    }
}

// variadic emplace_back (constexpr reference since C++20)
template <typename T>
template <class ...Args>
inline constexpr void Vec<T>::emplace_back(Args &&...rest) {
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(rest)...);
}

template <typename T> inline void printVec(const Vec<T> &tvec)
{
    std::cout << "Printing vector...\n";
    for (const auto &t : tvec) {
        std::cout << "\"" << t << "\" ";
    } std::cout << std::endl;
}

template <typename T> inline bool operator==(const Vec<T> &lhs, const Vec<T> &rhs)
{
    return (lhs.size() == rhs.size()) &&
    std::equal(lhs.begin(), lhs.end(), rhs.begin());
    
    // also had a for loop, but no need to reinvent the wheel
    // auto rhs_it = rhs.begin();
    // for (const auto &e : lhs)
    //     if (e != *rhs_it++)
    //         return false;
}

template <typename T> inline bool operator!=(const Vec<T> &lhs, const Vec<T> &rhs) { return !(lhs == rhs); }

template <typename T> inline bool operator<(const Vec<T> &lhs, const Vec<T> &rhs)
{
    auto rhs_it = rhs.begin();
    for (auto &e : lhs)
        if (e < *rhs_it++)
            return true;
    return false;
}

template <typename T> inline bool operator>(const Vec<T> &lhs, const Vec<T> &rhs) { return rhs < lhs; }
template <typename T> inline bool operator<=(const Vec<T> &lhs, const Vec<T> &rhs) { return !(lhs > rhs); }
template <typename T> inline bool operator>=(const Vec<T> &lhs, const Vec<T> &rhs) { return !(lhs < rhs); }

#endif /* Vec_h */
