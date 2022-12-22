# C++ Primer – [![](https://tokei.ekzhang.com/b1/github/ITHelpDec/CPP-Primer?category=code&style=plastic)](https://github.com/ITHelpDec/CPP-Primer)
My Journey Through C++ Primer 5th Edition

.:. Most recent submission (17/12/2022) .:.

```cpp
// Exercise 16.62:
/*
 Define your own version of hash<Sales_data> and define an unordered_multiset of Sales_data objects.
 Put several transactions into the container and print its contents.
*/

#ifndef Sales_data_hpp
#define Sales_data_hpp

#include <iostream>
#include <string>
#include <functional>
#include <unordered_set>

class Sales_data {
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
    
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend Sales_data operator-(const Sales_data&, const Sales_data&);
    
    friend bool operator<(const Sales_data&, const Sales_data&);
    friend bool operator>(const Sales_data&, const Sales_data&);
    friend bool operator<=(const Sales_data&, const Sales_data&);
    friend bool operator>=(const Sales_data&, const Sales_data&);
    
    // equality operators needed for hash function
    friend bool operator==(const Sales_data&, const Sales_data&);
    friend bool operator!=(const Sales_data&, const Sales_data&);
    
    // std::hash declared as friend in order to access private members
    friend std::hash<Sales_data>;
    
    // friend function to print contents of multiset
    friend void printSet(const std::unordered_multiset<Sales_data>&);
    
public:
    // default constructors
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) { }
    Sales_data(const std::string &bn, const std::size_t &us, const double &r)
        : bookNo(bn), units_sold(us), revenue(r) { }
    Sales_data(std::string &&bn, std::size_t &&us, double &&r)
        : bookNo(std::move(bn)), units_sold(std::move(us)), revenue(std::move(r)) { }
    
    // copy and copy-assignment
    Sales_data(const Sales_data &sd)
        : bookNo(sd.bookNo), units_sold(sd.units_sold), revenue(sd.revenue) { }
    Sales_data& operator=(const Sales_data&);
    
    // move and move-assignment
    Sales_data(Sales_data &&sd) noexcept
        : bookNo(std::move(sd.bookNo)), units_sold(std::exchange(sd.units_sold, 0)), revenue(std::exchange(sd.revenue, 0)) { }
    Sales_data& operator=(Sales_data&&) noexcept;
    
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
    
    explicit operator std::string() const   { return bookNo; }
    explicit operator double() const        { return revenue; }
    
    std::string isbn() const    { return bookNo; }
    double avg_price() const    { return revenue / units_sold; }
    
    void swap(Sales_data&, Sales_data&);
    
private:
    std::string bookNo;
    std::size_t units_sold = 0;
    double revenue = 0.0;
};

inline std::istream& operator>>(std::istream &is, Sales_data &in)
{
    double price = 0;
    is >> in.bookNo >> in.units_sold >> price;
    in.revenue = price * in.units_sold;
    return is;
}

inline std::ostream& operator<<(std::ostream &os, const Sales_data &out)
{
    os << out.bookNo << " " << out.units_sold << " " << out.avg_price();
    return os;
}

inline Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold + rhs.units_sold;
    sum.revenue = lhs.revenue + rhs.revenue;
    return sum;
}

inline Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold - rhs.units_sold;
    sum.revenue = lhs.revenue - rhs.revenue;
    return sum;
}

inline bool operator==(const Sales_data &sd1, const Sales_data &sd2) 
{
    return (sd1.bookNo == sd2.bookNo &&
    sd1.units_sold == sd2.units_sold &&
    sd1.revenue == sd2.revenue);
}

inline bool operator!=(const Sales_data &sd1, const Sales_data &sd2) 
{
    return !(sd1 == sd2);
}

inline bool operator<(const Sales_data &lhs, const Sales_data &rhs) 
{
    return lhs.avg_price() < rhs.avg_price();
}

inline bool operator>(const Sales_data &lhs, const Sales_data &rhs) 
{
    return rhs < lhs;
}

inline bool operator<=(const Sales_data &lhs, const Sales_data &rhs) 
{
    return !(rhs < lhs);
}

inline bool operator>=(const Sales_data &lhs, const Sales_data &rhs) 
{
    return !(lhs < rhs);
}

inline void Sales_data::swap(Sales_data &lhs, Sales_data &rhs) {
    using std::swap;
    swap(lhs.bookNo, rhs.bookNo);
    swap(lhs.units_sold, rhs.units_sold);
    swap(lhs.revenue, rhs.revenue);
}

inline Sales_data& Sales_data::operator=(const Sales_data &rhs)
{
    bookNo = rhs.bookNo;
    units_sold = rhs.units_sold;
    revenue = rhs.revenue;
    return *this;
}

inline Sales_data& Sales_data::operator=(Sales_data &&rhs) noexcept
{
    if (this != &rhs) {
        bookNo = std::move(rhs.bookNo);
        units_sold = std::exchange(rhs.units_sold, 0);
        revenue = std::exchange(rhs.revenue, 0);
    }
    return *this;
}

inline Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    Sales_data lhs_copy = *this;
    *this = lhs_copy + rhs;
    return *this;
}

inline Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
    Sales_data lhs_copy = *this;
    *this = lhs_copy - rhs;
    return *this;
}

void ret_Total()
{
    Sales_data total;
    if (std::cin >> total) {
        Sales_data trans;
        while(std::cin >> trans) {
            if (total.isbn() == trans.isbn())
                total + trans;
            else {
                std::cout << total << std::endl;
                total = trans;
            }
        } std::cout << total << std::endl;
    } else { std::cerr << "No data?!" << std::endl; }
}

// specialised hash function
namespace std {
template <> struct hash<Sales_data> {
    typedef size_t result_type;
    typedef Sales_data argument_type;
    
    size_t operator()(const Sales_data&) const;
    
};

size_t hash<Sales_data>::operator()(const Sales_data &s) const {
    return hash<string>()(s.bookNo) ^
    hash<size_t>()(s.units_sold) ^
    hash<double>()(s.revenue);
}

}

void printSet(const std::unordered_multiset<Sales_data> &sd_mset) {
    std::size_t count = 1;
    for (const auto &book : sd_mset) {
        std::cout << count << ": " << book.bookNo << ", " << book.units_sold << ", " << book.revenue << std::endl;
        ++count;
    } std::cout << std::endl;
}

#endif /* Sales_data_hpp */
```
```cpp
#include "Sales_data.hpp"

int main()
{
    Sales_data test1 = { "123-456-789-A", 2, 30 };
    Sales_data test2 = { "123-456-789-B", 2, 40 };
    Sales_data test3 = { "123-456-789-C", 2, 30 };
    
    std::unordered_multiset<Sales_data> sd_mset;
    sd_mset.insert(test1);
    sd_mset.insert(test2);
    sd_mset.insert(test3);
    
    printSet(sd_mset);
    
    std::cout << "sd_mset.bucket_count():     " << sd_mset.bucket_count() << "\n";
    std::cout << "sd_mset.max_bucket_count(): " << sd_mset.max_bucket_count() << "\n";
    std::cout << "sd_mset.bucket_size():      " << sd_mset.bucket_size(5) << "\n";
    std::cout << "sd_mset.bucket(test1):      " << sd_mset.bucket(test1) << "\n";
    std::cout << "sd_mset.bucket(test2):      " << sd_mset.bucket(test2) << "\n";
    std::cout << "sd_mset.bucket(test3):      " << sd_mset.bucket(test3) << "\n";
    std::cout << "sd_mset.load_factor():      " << sd_mset.load_factor() << "\n";
    std::cout << "sd_mset.max_load_factor():  " << sd_mset.max_load_factor() << std::endl;
    
    return 0;
}
```
```
output:
1: 123-456-789-A, 2, 30
2: 123-456-789-C, 2, 30
3: 123-456-789-B, 2, 40

sd_mset.bucket_count():     5
sd_mset.max_bucket_count(): 329406144173384850
sd_mset.bucket_size():      0
sd_mset.bucket(test1):      4
sd_mset.bucket(test2):      2
sd_mset.bucket(test3):      4
sd_mset.load_factor():      0.6
sd_mset.max_load_factor():  1
Program ended with exit code: 0
```
