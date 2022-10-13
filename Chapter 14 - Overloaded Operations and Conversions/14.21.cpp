// Exercise 14.21:
/*
 Write the Sales_data operators so that + does the actual addition and += calls +.
 Discuss the disadvantages of this approach compared to the way these operators were defined in § 14.3 (p. 560) and § 14.4 (p. 564).
 
 >> Swear we've discussed this already as well...functions attached below.
 >> Disadvantages, it involves more temporary objects, more overhead
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
    
    // += and -= operators are now member operators
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
    
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

// + operator
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold + rhs.units_sold;
    sum.revenue = lhs.revenue + rhs.revenue;
    return sum;
}

// - operator
Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold - rhs.units_sold;
    sum.revenue = lhs.revenue - rhs.revenue;
    return sum;
}

// += operator calls "+"
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    Sales_data lhs_copy = *this;
    *this = lhs_copy + rhs;
    return *this;
}

// "-=" operator calls "-"
Sales_data& Sales_data::operator-=(const Sales_data &rhs)
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
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "No data?!" << std::endl;
    }
}

int main()
{
    // ravlue reference construction
    std::cout << "Creating Sales_data \"test\"...\n";
    Sales_data test = { "12345", 1, 24.99 };
    std::cout << "test: " << test << std::endl;
    
    // lavlue reference construction
    std::string bn = "23456";
    std::size_t us = 2;
    double r = 70.00;
    
    std::cout << "\nCreating Sales_data \"test2\"...\n";
    Sales_data test2(bn,us,r);
    std::cout << "test2: " << test2 << std::endl;
    
    // input test
    // 34567 3 49.99
    std::cout << "\nInput data for \"test3\": ";
    Sales_data test3;
    std::cin >> test3;
    std::cout << "test3: " << test3 << std::endl;
    
    std::cout << "\nAdding test to test2, then assigning to test3...\n";
    test3 = test2 + test;
    std::cout << "test3: " << test3 << std::endl;
    
    std::cout << "\nSubtracting test from test2, then assigning to test3...\n";
    test3 = test2 - test;
    std::cout << "test3: " << test3 << std::endl;
    
    std::cout << "\n+=...\n";
    test3 += test2;
    std::cout << "test3: " << test3 << std::endl;
    
    std::cout << "\n-=...\n";
    test3 -= test2;
    std::cout << "test3: " << test3 << std::endl;
    
    // ret_Total();;

    return 0;
}
