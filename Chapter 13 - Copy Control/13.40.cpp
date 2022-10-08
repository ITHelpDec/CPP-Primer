// Exercise 13.40:
/*
 Add a constructor that takes an initializer_list<string> to your StrVec class.
*/

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    // see below
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();
    
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

void StrVec::free()
{
    if (elements) {
        for (auto p = first_free; p != elements; /* empty */ )
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

StrVec::~StrVec() { free(); }

StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto rhsdata = alloc_n_cpy(rhs.begin(), rhs.end());
    free();
    
    elements = rhsdata.first;
    first_free = cap = rhsdata.second;
    
    return *this;
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto newdata = alloc.allocate(newcapacity);
    auto dest = newdata;
    auto elem = elements;
    
    for (std::size_t i = 0; i != size(); ++i)
        alloc.construct(dest++, std::move(*elem++));
    
    free();
    
    elements = newdata;
    first_free = dest;
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
    std::cout << "Printing vector...\n\"";
    for (const auto &e : svec) {
        std::cout << e << "\" \"";
    } std::cout << "\"" << std::endl;
}

int main()
{
    std::cout << "Creating new StrVec of 3 elements...\n";
    StrVec s1;
    s1.push_back("man");
    s1.push_back("bear");
    s1.push_back("pig");
    
    std::cout << "s1.size() = " << s1.size() << std::endl;
    std::cout << "s1.capacity() = " << s1.capacity() << std::endl;
    vprint(s1);
    
    std::cout << "\nAttempting to change reserve to 2...\n";
    s1.reserve(2);
    
    std::cout << "\nAttempting to change reserve to 10...\n";
    s1.reserve(8);
    std::cout << "s1.size() = " << s1.size() << std::endl;
    std::cout << "s1.capacity() = " << s1.capacity() << std::endl;
    
    std::cout << "\nAttempting to change size to 3...\n";
    s1.resize(3);
    
    std::cout << "\nAttempting to resize the vector to 1...\n";
    s1.resize(1);
    std::cout << "s1.size() = " << s1.size() << std::endl;
    std::cout << "s1.capacity() = " << s1.capacity() << std::endl;
    
    std::cout << "\nNow attempting to resize the vector to 10...\n";
    s1.resize(10, "woof");
    std::cout << "s1.size() = " << s1.size() << std::endl;
    std::cout << "s1.capacity() = " << s1.capacity() << std::endl;
    
    std::cout << "\nAttempting to resize the vector to 9 with a string argument...\n";
    s1.resize(9, "woof");
    
    vprint(s1);
    
    return 0;
}
