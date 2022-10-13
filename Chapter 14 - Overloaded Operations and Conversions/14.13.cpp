// Exercise 14.13:
/*
 Which other arithmetic operators (Table 4.1 (p. 139)), if any, do you think Sales_data ought to support? Define any you think the class should include.
 
 >> subtraction, so "-" and "-=" member and non-member operators
 >> Code from previous Sales_data code was incorrect - specifically addition and subtraction
*/

#include <iostream>
#include <string>

class Sales_data {
    // new friend funcitons for + and -
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
    
    // += and -= operators
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

//
// += and -= needed for + and - to work further down
//

// += operator
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    // not adding bookNo; only units_sold and revenue
    units_sold += rhs.units_sold;
    revenue -= rhs.revenue;
    return *this;
}

// -= operator
Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
    // as above
    units_sold -= rhs.units_sold;
    revenue -= rhs.revenue;
    return *this;
}

// + operator changed - the code below was incorrect
// Sales_data& Sales_data::operator-(const Sales_data &rhs) { return *this - rhs; }
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    // copy data from lhs into sum
    Sales_data sum = lhs;
    
    // use lhs += rhs function we created above and return sum
    sum += rhs;
    return sum;
}

// - operator
Sales_data operator-(const Sales_data &lhs, const Sales_data &rhs)
{
    // as above, only using "-"
    Sales_data sum = lhs;
    sum -= rhs;
    return sum;
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
    
    // ret_Total();;

    return 0;
}
