
// Exercise 13.52:
/*
 Explain in detail what happens in the assignments of the HasPtr objects on page 541.
 In particular, describe step by step what happens to values of hp, hp2, and of the rhs parameter in the HasPtr assignment operator.
*/

#include <string>
#include <iostream>
#include <vector>

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    friend std::ostream &print(std::ostream&, const HasPtr&);
    
public:
    HasPtr() {}
    HasPtr(const std::string &s, const int &i) : ps(new std::string(s)), i(i), use(new std::size_t(1)) { }
    
    HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i), use(o.use) { ++*use;  }
    
    HasPtr& operator=(const HasPtr&);
    bool operator<(const HasPtr&) const;
    
    ~HasPtr();
    
    // move constructor and move-assingment operator added from page 540
    // what about "i" and "use"?
    HasPtr(HasPtr&&) noexcept;
    
    HasPtr& operator=(HasPtr&&);
    // not sure why the book doesn't use the && like below
    // code is considered ambiguous and will not compile
    // HasPtr& operator=(HasPtr rhs);
private:
    std::string *ps;
    int i;
    std::size_t *use;
};

HasPtr::~HasPtr()
{
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    ++*rhs.use;
    std::string *pstmp = new std::string(*rhs.ps);
    
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    
    ps = pstmp;
    i = rhs.i;
    use = rhs.use;
    
    std::cout << "(Copy-assignment operator called)" << std::endl;
    
    return *this;
}


// move constructor
HasPtr::HasPtr(HasPtr &&rhs) noexcept
{
    // move
    ps = rhs.ps;
    i = rhs.i;
    
    rhs.ps = 0;
    
    std::cout << "(Move constructor called)" << std::endl;
}

// move-assignment operator
HasPtr& HasPtr::operator=(HasPtr &&rhs)
{
    swap(*this, rhs);
    std::cout << "(Move-assignment operator called)" << std::endl;
    return *this;
}


bool HasPtr::operator<(const HasPtr &rhs) const { return i < rhs.i; }

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i,rhs.i);
    swap(lhs.use, rhs.use);
}

std::ostream &print(std::ostream &os, const HasPtr &hp)
{
    os << "ps = " << *hp.ps << "\ti = " << hp.i << "\tuse = " << *hp.use;
    return os;
}

int main()
{
    std::cout << "Creating two HasPtr objects...\n";
    HasPtr hp("totally", 1);
    HasPtr hp2("totally", 2);
    
    print(std::cout, hp) << std::endl;
    print(std::cout, hp2) << std::endl;
    
    std::cout << "\nAttempting \"hp = hp2\"...\n";
    hp = hp2;
    
    // "hp2 is an lvalue; copy constructor used to copy hp2"
    // copy constructor is detailed above
    
    print(std::cout, hp) << std::endl;
    print(std::cout, hp2) << std::endl;
    
    
    std::cout << "\nAttempting \"hp = std::move(hp2)\"...\n";
    hp = std::move(hp2);
    
    // std::move(hp2) returns an rvalue, so move-assignment operator will be called (if it exists)
    // "move constructor moves hp2"
    
    print(std::cout, hp) << std::endl;
    print(std::cout, hp2) << std::endl;
    
    return 0;
}
