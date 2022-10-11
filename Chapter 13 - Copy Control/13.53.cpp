// Exercise 13.53:
/*
 As a matter of low-level efficiency, the HasPtr assignment operator is not ideal.
 Explain why.
 Implement a copy-assignment and move-assignment operator for HasPtr and compare the operations executed in your new move-assignment operator versus the copy-and-swap version.
 
 // In the shared copy-move-assignment operator from the last exercise, we do not prepare protect against self-assignment, nor de we prepare the rhs for destruction
 // Updated version below in comments
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
    
    HasPtr& operator=(const HasPtr&);
    bool operator<(const HasPtr&) const;
    
    ~HasPtr();
    
    // turns out I created a move-assignment operator unintentionally in the last exercise
    HasPtr(HasPtr&&) noexcept;
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

HasPtr& HasPtr::operator=(const HasPtr &rhs)
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
    // decrease occurence count, because move implies deletion
    --*rhs.use;
    
    // clear space to prevent memory leak
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    
    // move
    ps = std::move(rhs.ps);
    i = std::move(rhs.i);
    use = std::move(rhs.use);
    
    // clean up
    rhs.ps = nullptr;
    rhs.i = 0;
    
    std::cout << "(Move constructor called)" << std::endl;
}

// move-assignment operator
HasPtr& HasPtr::operator=(HasPtr &&rhs) noexcept
{
    // check for self-assignment
    if (this != &rhs) {
        
        // clear lhs to prevent memory leak
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        // if moving, rhs occurences will decrease by one
        --*rhs.use;
        
        // move
        ps = std::move(rhs.ps);
        i = std::move(rhs.i);
        use = std::move(rhs.use);
        
        // clean up
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
