// Exercise 13.54:
/*
 What would happen if we defined a HasPtr move-assignment operator but did not change the copy-and-swap operator?
 Write code to test your answer.
 
 // The compiler will complain about overloading ambiguity.
 // "Use of overloaded operator '=' is ambiguous (with operand types 'HasPtr' and 'typename remove_reference<HasPtr &>::type' (aka 'HasPtr'))"
*/

#include <string>
#include <iostream>
#include <vector>

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    friend std::ostream &print(std::ostream&, const HasPtr&);
    
public:
    HasPtr() {}
    HasPtr(const std::string &s, const int &i) : ps(new std::string(s)), i(i), use(new std::size_t(1))
    {
        std::cout << "(Constructor #2 called)" << std::endl;
    }
    
    HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i), use(o.use)
    {
        ++*use;
        std::cout << "(Copy constructor called)" << std::endl;
    }
    
    // HasPtr& operator=(const HasPtr&);
    // copy-and-swap terturned to normal
    HasPtr& operator=(HasPtr);
    bool operator<(const HasPtr&) const;
    
    ~HasPtr();
    
    HasPtr(HasPtr&&) noexcept;
    // ove-assignment operator still there
    HasPtr& operator=(HasPtr&&) noexcept;
    
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
    std::cout << "use: " << *(this->use) << std::endl;
    std::cout << "(Destructor called)" << std::endl;
}

HasPtr& HasPtr::operator=(HasPtr rhs)
{
    ++*rhs.use;
    std::string *pstmp = new std::string(*rhs.ps);
    
    if (--*use == 0) { delete ps; delete use; }
    
    ps = pstmp;
    i = rhs.i;
    use = rhs.use;
    
    std::cout << "(Copy-assignment operator called)" << std::endl;

    return *this;
}

// move constructor
HasPtr::HasPtr(HasPtr &&rhs) noexcept
{
    --*rhs.use;
    
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    
    ps = std::move(rhs.ps);
    i = std::move(rhs.i);
    use = std::move(rhs.use);
    
    rhs.ps = nullptr;
    rhs.i = 0;
    
    std::cout << "(Move constructor called)" << std::endl;
}

// move-assignment operator
HasPtr& HasPtr::operator=(HasPtr &&rhs) noexcept
{
    if (this != &rhs) {
        
        if (--*use == 0) {
            delete ps;
            delete use;
        }

        --*rhs.use;
        
        ps = std::move(rhs.ps);
        i = std::move(rhs.i);
        use = std::move(rhs.use);
        
        rhs.ps = nullptr;
        rhs.i = 0;
        
        std::cout << "(Move-assignment operator called)" << std::endl;
    }
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
    HasPtr hp2("cereal", 2);
    
    std::cout << "hp:  "; print(std::cout, hp) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    
    std::cout << "\nAttempting \"hp = hp2\"...\n";
    hp = hp2;
    
    // "hp2 is an lvalue; copy constructor used to copy hp2"
    // copy constructor is detailed above
    
    std::cout << "hp:  "; print(std::cout, hp) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    
    std::cout << "\nAttempting \"HasPtr hp3 = hp\"...\n";
    HasPtr hp3 = hp;
    std::cout << "hp:  "; print(std::cout, hp) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl;
    
    std::cout << "\nAttempting \"hp = std::move(hp2)\"...\n";
    hp = std::move(hp3);
    
    std::cout << "hp:  "; print(std::cout, hp) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    // std::cout << "hp3: "; print(std::cout, hp3) << std::endl;
    // we have called std::move on hp2, therefore we intend to prepare it for destruction
    
    return 0;
}
