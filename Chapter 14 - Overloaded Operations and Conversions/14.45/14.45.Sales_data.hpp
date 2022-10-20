
#ifndef Sales_data_hpp
#define Sales_data_hpp

#include <iostream>
#include <string>

class Sales_data {
    friend Sales_data operator+(const Sales_data&, const Sales_data&);
    friend Sales_data operator-(const Sales_data&, const Sales_data&);
    
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
    
public:
    Sales_data() = default;
    
    Sales_data(std::string &&bn, std::size_t &&us, double &&r) : bookNo(bn), units_sold(us), revenue(r)
    { std::cout << "(rvalue reference used)" << std::endl; }
    
    Sales_data(const std::string &bn, const std::size_t &us, const double &r) : bookNo(bn), units_sold(us), revenue(r)
    { std::cout << "(lvalue reference used)" << std::endl; }
    
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
    
    Sales_data& operator=(std::string&&);
    
    // explicit conversion operators
    explicit operator std::string() const { return bookNo; }
    explicit operator double() const { return revenue; }
    
    std::string isbn() { return bookNo; }
    double avg_price() const { return revenue / units_sold; }
    
private:
    std::string bookNo;
    std::size_t units_sold = 0;
    double revenue = 0.0;
};

#endif /* Sales_data_hpp */
