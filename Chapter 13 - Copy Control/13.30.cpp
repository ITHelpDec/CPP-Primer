// Exercise 13.30:
/*
 Write and test a swap function for your valuelike version of HasPtr.
 Give your swap a print statement that notes when it is executed.
 
 >> Hoping there aren't any memory leaks
*/

#include <string>
#include <iostream>

class HasPtr {
    // declare swap and print functions
    friend void swap(HasPtr&, HasPtr&);
    friend std::ostream &print(std::ostream&, const HasPtr&);
    
public:
    HasPtr() {}
    HasPtr(const std::string &s, const int &i) : ps(new std::string(s)), i(i), use(new std::size_t(1)) { }
    
    HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i), use(o.use) { ++*use;  }
    
    HasPtr& operator=(const HasPtr&);
    
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;
};

// destructor
HasPtr::~HasPtr()
{
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    std::cout << *use << std::endl;
}

HasPtr& HasPtr::operator=(const HasPtr &rhs)
{
    // increment right hand operands
    ++*rhs.use;
    std::string *pstmp = new std::string(*rhs.ps);
    
    // decrement left hand operands
    if (--*use == 0) {
        delete ps;
        delete use;
    }
    
    // copy data from right hand operands into this object
    ps = pstmp;
    i = rhs.i;
    use = rhs.use;
    
    return *this;
}

// inline to optimise code
inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i,rhs.i);
    swap(lhs.use, rhs.use);
}

// print function
std::ostream &print(std::ostream &os, const HasPtr &hp)
{
    os << "ps = " << *hp.ps << "\ti = " << hp.i << "\tuse = " << *hp.use;
    return os;
}

int main()
{
    std::cout << "Creating hp1, hp2 and hp3:\n";
    HasPtr hp1("man", 1);
    HasPtr hp2("bear", 2);
    HasPtr hp3("pig", 3);
    
    std::cout << "hp1: "; print(std::cout, hp1) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl << std::endl;
    
    std::cout << "Creating hp4(hp1):\n";
    HasPtr hp4(hp1);
    
    std::cout << "hp1: "; print(std::cout, hp1) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl;
    std::cout << "hp4: "; print(std::cout, hp4) << std::endl << std::endl;
    
    std::cout << "Setting hp4 = hp2:\n";
    hp4 = hp2;
    
    std::cout << "hp1: "; print(std::cout, hp1) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl;
    std::cout << "hp4: "; print(std::cout, hp4) << std::endl << std::endl;
    
    std::cout << "Swapping hp1 and hp2:\n";
    swap(hp1, hp2);
    
    std::cout << "hp1: "; print(std::cout, hp1) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl;
    std::cout << "hp4: "; print(std::cout, hp4) << std::endl << std::endl;
    
    std::cout << "SDestroying objects...\n";
    
    return 0;
}
