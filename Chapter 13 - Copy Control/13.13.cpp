// Exercise 13.13:
/*
 A good way to understand copy-control members and constructors is to define a simple class with these members in which each member prints its name:
*/
/*
 (1) Add the copy-assignment operator and destructor to X and write a program using X objects in various ways:
 (2) Pass them as nonreference and reference parameters;
 (3) dynamically allocate them;
 (4) put them in containers;and so forth.
 (5) Study the output until you are certain you understand when and why each copy-control member is used.
 (6) As you read the output, remember that the compiler can omit calls to the copy constructor.
*/

#include <iostream>
#include <vector>

struct X {
    // default constructor
    X() { std::cout << "X()" << std::endl; }
    // copy constructor
    X(const X &original) { std::cout << "X(const X&) copy" << std::endl; }
    // (1) copy-assignment constructor
    X& operator=(const X &rhs) { std::cout << "X(const X&) copy-assignment" << std::endl; return *this; }
    // (1) destructor
    ~X() {  std::cout << "~X()" << std::endl; }
private:
    std::size_t count = 0;
};

// (2) nonreference parameter
void nonRefFoo(X x)
{
    //
}

// (2) reference parameter
void refFoo(const X &x)
{
    //
}

int main()
{
    X x1;
    X x2(x1);
    x1 = x2;
    
    nonRefFoo(x1);
    refFoo(x1);
    
    // (3) dynamically allocate (remember to delete)
    X *x3 = new X(x1);
    delete x3;
    x3 = nullptr;
    
    // (4) use in a conatiner
    std::vector<X> xvec= { x1 };
    xvec.push_back(x2);
    xvec.pop_back();
    xvec.pop_back();
    
    return 0;
}
