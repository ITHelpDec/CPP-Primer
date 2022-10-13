// Exercise 14.22:
/*
 Define a version of the assignment operator that can assign a string representing an ISBN to a Sales_data.
*/

#include <iostream>
#include <string>

class Sales_data {
    // "+" and "-" operators are now friends that call "+" and "-"
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
    
    // "=" member operator
    Sales_data& operator=(std::string&&);
    
    std::string isbn() { return bookNo; }
    double avg_price() const { return revenue / units_sold; }
    
private:
    std::string bookNo;
    std::size_t units_sold = 0;
    double revenue = 0.0;
};

std::istream& operator>>(std::istream &is, Sales_data &in)
{
    double price = 0;
    is >> in.bookNo >> in.units_sold >> price;
    in.revenue = price * in.units_sold;
    return is;
}

std::ostream& operator<<(std::ostream &os, const Sales_data &out)
{
    double price = 0;
    os << out.bookNo << " " << out.units_sold << " " << out.avg_price();
    return os;;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold + rhs.units_sold;
    sum.revenue = lhs.revenue + rhs.revenue;
    return sum;
}

Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold - rhs.units_sold;
    sum.revenue = lhs.revenue - rhs.revenue;
    return sum;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    Sales_data lhs_copy = *this;
    *this = lhs_copy + rhs;
    return *this;
}

Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
    Sales_data lhs_copy = *this;
    *this = lhs_copy - rhs;
    return *this;
}

// "=" operator, assigning string to Sales_data object
Sales_data& Sales_data::operator=(std::string &&rhs)
{
    bookNo = rhs;
    std::cout << "(operator= used)" << std::endl;
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
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}

int main()
{
    std::cout << "Creating Sales_data object (s)...\n";
    Sales_data s = { "12345", 2, 24.99 };
    std::cout << s << std::endl;
    
    std::cout << "\nUsing operator= to assign a new string...\n";
    s = "manbearpig";
    std::cout << s << std::endl;
    
    return 0;
}
