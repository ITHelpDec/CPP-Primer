// Exercise 14.23:
/*
 Define an initializer_list assignment operator for your version of the StrVec class.
*/

#include <memory>
#include <string>
#include <initializer_list>
#include <iostream>

class StrVec {
    friend std::ostream& operator<<(std::ostream&, const StrVec&);
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();
    
    StrVec(StrVec&&) noexcept;
    StrVec& operator=(StrVec&&) noexcept;
    
    // initializer_list operator (trying an rvalue reference)
    StrVec& operator=(std::initializer_list<std::string>&&);
    
    void push_back(const std::string&);
    
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    
    void reserve(const int&);
    void resize(const int&);
    void resize(const int&, const std::string&);
    
private:
    static std::allocator<std::string> alloc;
    
    void chk_n_alloc() { if (size() == capacity()) reallocate(); }
    
    std::pair<std::string*, std::string*> alloc_n_cpy(const std::string*, const std::string*);
    std::pair<std::string*, std::string*> alloc_n_move(std::string*, std::string*);
    
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

// move constructor
StrVec::StrVec(StrVec &&sv) noexcept
{
    auto newdata = alloc_n_move(sv.begin(), sv.end());
    elements = std::move(newdata.first);
    first_free = cap = std::move(newdata.second);
    // REMEMBER TO LEAVE DESTRUCTABLE
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

// move-assignment operator
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

// introduced "<<" operator
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

void StrVec::resize(const int &n)
{
    if (n < size()) {
        while (size() != n && elements) {
            alloc.destroy(--first_free);
        }
        return;
    }
    
    if (n > size()) {
        while (size() != n) {
            push_back("");
        }
        return;
    }
    
    if (n < 0) {
        std::cerr << "Cannot have a negative size." << std::endl;
        return;
    }
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

void vprint(const StrVec &svec)
{
    std::cout << "Printing vector...\n";
    for (const auto &e : svec) {
        std::cout << "\"" << e << "\" ";
    } std::cout << std::endl;
}

int main()
{
    StrVec svec;
    svec = { "man", "bear", "pig" };
    
    vprint(svec);
    
    
    std::cout << "\nPrinting svec...\n" << svec << std::endl;

    return 0;
 }
