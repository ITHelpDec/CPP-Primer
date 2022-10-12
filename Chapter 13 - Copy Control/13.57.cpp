// Exercise 13.57:
/*
 What if we defined sorted as:
 
 // Foo Foo::sorted() const & { return Foo(*this).sorted(); }
*/

#include <vector>
#include <algorithm>
#include <iostream>

class Foo {
    
public:
    // can run on modifiable rvalues
    Foo sorted() &&;
    
    // can run on any kind of Foo
    Foo sorted() const &;
    
    // test function with slightly different body
    Foo sorted2() const &;
    
    //iterators
    std::vector<int>::iterator begin() { return data.begin(); }
    std::vector<int>::iterator end() { return data.end(); }
    
private:
    std::vector<int> data = { 5, 4, 3, 2, 1 };
};

Foo Foo::sorted() && {
    std::sort(data.begin(), data.end());
    std::cout << "(.sorted() &&)" << std::endl;
    return *this;
}

// with an additional sorted2() const &, this works
// without an additional Foo Foo::sorted() funciton const &, this will not work
// compile code to see output
Foo Foo::sorted() const & {
    return Foo(*this).sorted();
}

Foo Foo::sorted2() const & {
    Foo ret(*this);
    std::sort(ret.data.begin(), ret.data.end());
    std::cout << "(.sorted() const &)" << std::endl;
    return ret;
}

int main()
{
    std::cout << "Creating Foo object (f)...\n";
    Foo f;
    
    std::cout << "\nPrinting \"&e : f\"...\n";
    for (const auto &e : f) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    std::cout << "\nPrinting \"const &e : f.sorted()\"...\n";
    for (const auto &e : f.sorted()) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    std::cout << "\nPrinting \"const &e : f.sorted()\"...\n";
    for (const auto &e : f.sorted2()) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    std::cout << "\nSetting all values in f to 0...";
    for (auto &e : f) {
        e = 1;
    } std::cout << std::endl;
    
    std::cout << "\nPrinting \"&e : f\"...\n";
    for (const auto &e : f) {
        std::cout << e << " ";
    } std::cout << std::endl;
    
    return 0;
}
