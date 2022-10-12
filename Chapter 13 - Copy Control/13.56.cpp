// Exercise 13.55:
/*
 What would happen if we defined sorted as:
 
 Foo Foo::sorted() const & {
     Foo ret(*this);
     std::cout << "(.sorted() const &)" << std::endl;
     return ret.sorted();
 
 // The function would call itself recursively, but we can fix it by calling the first function something else like sorted2().
 // This then calls sorted() or sorted2(), so it looks like ret.data.sorted()
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

Foo Foo::sorted() const & {
    Foo ret(*this);
    std::sort(ret.data.begin(), ret.data.end());
    std::cout << "(.sorted() const &)" << std::endl;
    return ret;
}

Foo Foo::sorted2() const & {
    Foo ret(*this);
    std::cout << "(.sorted2() const &)" << std::endl;
    return ret.sorted();
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
}
