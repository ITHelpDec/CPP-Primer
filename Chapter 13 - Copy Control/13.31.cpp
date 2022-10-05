#include <string>
#include <iostream>
// add vector header
#include <vector>

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    friend std::ostream &print(std::ostream&, const HasPtr&);
    
public:
    HasPtr() {}
    HasPtr(const std::string &s, const int &i) : ps(new std::string(s)), i(i), use(new std::size_t(1)) { }
    
    HasPtr(const HasPtr &o) : ps(new std::string(*o.ps)), i(o.i), use(o.use) { ++*use;  }
    
    HasPtr& operator=(const HasPtr&);
    
    // < operator declaration
    bool operator<(const HasPtr&) const;
    
    ~HasPtr();
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
    
    return *this;
}

// < operator expansion
// will use "<" between "i"

bool HasPtr::operator<(const HasPtr &rhs) const
{
    return i < rhs.i;
}

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    // added std::cout for swhen swap is called
    std::cout << "(Swap called)" << std::endl;
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
    std::cout << "Creating hp1, hp2 and hp3...";
    HasPtr hp1("bear", 2);
    HasPtr hp2("pig", 3);
    HasPtr hp3("man", 1);
    
    std::cout << "hp1: "; print(std::cout, hp1) << std::endl;
    std::cout << "hp2: "; print(std::cout, hp2) << std::endl;
    std::cout << "hp3: "; print(std::cout, hp3) << std::endl << std::endl;
    
    // add objects to vector
    std::cout << "Adding these objects to a vector...";
    std::vector<HasPtr> hpvec = { hp1, hp2, hp3 };
    
    std::cout << "\nPrinting vector...";
    for (const auto &e : hpvec) {
        print(std::cout, e) << std::endl;
    } std::cout << std::endl;
    
    // sort the vector
    // "sort" will not work without "<" operator
    std::cout << "Sorting vector...\n";
    std::sort(hpvec.begin(), hpvec.end());
    
    std::cout << "\nPrinting sorted vector...\n";
    for (const auto &e : hpvec) {
        print(std::cout, e) << std::endl;
    } std::cout << std::endl;
    
    return 0;
}
