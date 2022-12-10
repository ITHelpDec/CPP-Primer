// Exercise 16.28:
/*
 Write your own versions of shared_ptr and unique_ptr.
 
 // This is a terrible exercise...especially with no official solution.
 // overall structure based off cppreference documentation
*/

#include <iostream>
#include <string>

// the deleter must be storeed as a pointer or as a class that encapsulates a pointer
class DebugDelete {
public:
    DebugDelete(std::ostream &os = std::cerr, const std::string &s = "shared_ptr") : os_(os), type(s) { }
    
    // shared_ptr does not hold the deleter as a member function
    template <typename T> void operator()(T *p) const
    {
        os_ << "::DebugDelete()\n";
        delete p;
    }
    
private:
    std::ostream &os_;
    std::string type; // taken from source code example
};

template <typename T> class shared_ptr {
public:
    // "we can construct a shared_ptr using a deleter of one type..."
    // "let's assume that shared_ptr stores the pointer it manages in a member named "p"...,"
    // "...and that the deleter is accessed through a member named "del"."
    template <typename Y, class Deleter> explicit shared_ptr(Y *ptr, Deleter d) : p(ptr), del(d) { ++ref_count; }
    
    // "the shared_ptr destructor must include a statement such as..."
    // ~shared_ptr() { del ? del(p) : delete p; } doesn't work
    ~shared_ptr() { del(p); }
    
    // "...and subsequently use reset to give that same shared pointer a different type of deleter."
    template <typename Y, class Deleter> void reset(Y *ptr, Deleter d) { shared_ptr(ptr, d).swap(*this); }
    
    // exchanges the stored pointer values and the ownerships of *this and r
    void swap(shared_ptr &r) noexcept
    {
        using std::swap;
        swap(p, r.p);
        swap(ref_count, r.ref_count);
    }
    
    // Value of type 'Deleter' is not contextually convertible to 'bool'
    
private:
    T *p = nullptr;
    DebugDelete del;
    std::size_t ref_count = 0;
};

int main()
{
    shared_ptr<int> isp(new int, DebugDelete());
    
    return 0;
}
