// Exercise 19.25:
/*
 Write assignment operators that take values of each type in the union.
 
 >> Didn't realise I had already done this in exercise 19.23
*/

#ifndef Sales_data_hpp
#define Sales_data_hpp

#include <iostream>
#include <string>
#include <functional>
#include <unordered_set>
#include <stdexcept>

class out_of_stock;
class isbn_mismatch;

class Sales_data {
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
    
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend Sales_data operator-(const Sales_data&, const Sales_data&);
    
    friend bool operator<(const Sales_data&, const Sales_data&);
    friend bool operator>(const Sales_data&, const Sales_data&);
    friend bool operator<=(const Sales_data&, const Sales_data&);
    friend bool operator>=(const Sales_data&, const Sales_data&);
    
    friend bool operator==(const Sales_data&, const Sales_data&);
    friend bool operator!=(const Sales_data&, const Sales_data&);
    
    friend std::hash<Sales_data>;
    
    friend void printSet(const std::unordered_multiset<Sales_data>&);
    
public:
    Sales_data() = default;
    Sales_data(const std::string &s) : bookNo(s) { }
    Sales_data(const std::string &bn, const std::size_t &us, const double &r)
        : bookNo(bn), units_sold(us), revenue(r) { }
    Sales_data(std::string &&bn, std::size_t &&us, double &&r)
        : bookNo(std::move(bn)), units_sold(std::move(us)), revenue(std::move(r)) { }
    
    Sales_data(const Sales_data &sd)
        : bookNo(sd.bookNo), units_sold(sd.units_sold), revenue(sd.revenue) { }
    
    Sales_data& operator=(const Sales_data&);
    
    Sales_data(Sales_data &&sd) noexcept
        : bookNo(std::move(sd.bookNo)),
          units_sold(std::exchange(sd.units_sold, 0)),
          revenue(std::exchange(sd.revenue, 0)) { }
    
    Sales_data& operator=(Sales_data&&) noexcept;
    
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
    
    explicit operator std::string() const   { return bookNo; }
    explicit operator double() const        { return revenue; }
    
    std::string isbn() const    { return bookNo; }
    double avg_price() const    { return revenue / units_sold; }
    
    void swap(Sales_data&, Sales_data&);
    
    // necessary helper function
    static const std::string Sales_data::*isbnPtr() { return &Sales_data::bookNo; }
    
private:
    std::string bookNo;
    std::size_t units_sold = 0;
    double revenue = 0.0;
};

class out_of_stock : public std::runtime_error {
public:
    explicit out_of_stock(const std::string &s) : std::runtime_error(s) {  }
};

class isbn_mismatch : public std::logic_error {
public:
    explicit isbn_mismatch(const std::string &s) : std::logic_error(s) { }
    
    isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs)
        : std::logic_error(s), left_(lhs), right_(rhs) { }
    
    const std::string left_, right_;
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
    Sales_data temp = lhs;
    temp += rhs;
    return temp;
}

inline Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data temp = lhs;
    temp -= rhs;
    return temp;
}

inline bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.bookNo == rhs.bookNo &&
           lhs.units_sold == rhs.units_sold &&
           lhs.revenue == rhs.revenue;
}

inline bool operator!=(const Sales_data &lhs, const Sales_data &sd2)
{
    return !(lhs == sd2);
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

inline void Sales_data::swap(Sales_data &lhs, Sales_data &rhs)
{
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
    if (bookNo != rhs.bookNo)
        throw isbn_mismatch("wrong isbns", bookNo, rhs.bookNo);
    Sales_data lhs_copy = *this;
    *this = lhs_copy + rhs;
    return *this;
}

inline Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
    if (bookNo != rhs.bookNo)
        throw isbn_mismatch("wrong isbns", bookNo, rhs.bookNo);
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
