// Exercise 13.39:
/*
 Write your own version of StrVec, including versions of reserve,
 capacity (§ 9.4, p. 356), and resize (§ 9.3.5, p. 352).
*/

#include <memory>
#include <vector>
#include <string>
#include <iostream>

class StrVec {
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(const StrVec&);
    StrVec& operator=(const StrVec&);
    ~StrVec();
    
    void push_back(const std::string&);
    
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    
    // functions required for exercise
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
    // ensure that there is room for another element
    chk_n_alloc();
    
    // construct a copy of s in the element to which first_free points
    // "The first argument to construct must be a pointer to unconstructed space allocated by a all to allocate.
    // The remaining arguments determine which constructor to use to construct hte object that will go in that space"
    // i.e. std::string copy constructor
    // ++ increments first_free to point to the next unconstructed element
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

// "A call to reserve changes the capacity of the vector only if the requested space exceeds the current capacity""
void StrVec::reserve(const int &n)
{
    if (n < 0) {
        std::cerr << "Cannot reserve a negative value." << std::endl;
        return;
    }
    // check the requested size is greater than current capacity
    if (!(n > capacity())) {
        std::cerr << "Cannot reduce capacity any lower than current capacity of " << cap  << "." << std::endl;
        return;
    }
    // allocate more memory, but do not populate
    alloc.allocate(n);
    
    // update capacity (note: no of elements and first_free do not change)
    cap = elements + n;
}

// first version of resize -> "c.resize(n)"
void StrVec::resize(const int &n)
{
    // if n is smaller than current size, we must remove elements
    if (n < size()) {
        while (size() != n && elements) {
            alloc.destroy(--first_free);
            
            // !!! we do not need to deallocate memory after destruction !!!
            // resize affects elements, not capacity
            // alloc.deallocate(--first_free, const std::size_t &n);
            
            // "If resize shrinks the container, then iterators, references, and pointers to the deleted elements are invalidated."

        }
        // std::cout << *elements << " " << *first_free << " " << *cap << std::endl;
        return;
    }
    // if n is greater than current size
    if (n > size()) {
        while (size() != n) {
            push_back("");
        }
        return;
    }
    // if n is a negative number
    // normally i would use std::size_t, but .resize(-1) would produce unwanted results
    if (n < 0) {
        std::cerr << "Cannot have a negative size." << std::endl;
        return;
    }
    // any other result would mean n == size()
    std::cerr << "StrVec already of size " << n << std::endl;
}

// second version of resize -> "c.resize(n, t)"
// this version will only work if n > size()
void StrVec::resize(const int &n, const std::string &s)
{
    if (n > size()) {
        while (n != size())
            push_back(s);
    } else {
        std::cerr << "Must enter a number greater than current size.\n" << std::endl;
    }
}

// print function for debugging
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
