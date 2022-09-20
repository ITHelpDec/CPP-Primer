// Exercise 8.6:
/*
 Rewrite the bookstore program from § 7.1.1 (p. 256) to read its transactions from a file.
 Pass the name of the file as an argument to main (§ 6.2.5, p. 218).
*/

#include <iostream>
#include <string>
#include <fstream>

class Sales_data {
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    
public:
    // default constructors
    Sales_data(std::string s, unsigned cnt, double price) : bookNo(s), units_sold(cnt), revenue(cnt*price) {}
    Sales_data() : Sales_data("", 0, 0) {}
    
    // explicit constructors
    explicit Sales_data(std::string s) : Sales_data(s, 0, 0) {}
    explicit Sales_data(std::istream &is) : Sales_data() { read(is, *this); }
    
    Sales_data &combine(const Sales_data&);
    std::string isbn() const { return bookNo; }

private:
    double avg_price() const;   // inlined outside of the class body
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    
    
};

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;   // add the members of rhs into
    revenue += rhs.revenue;         // the members of this object
    return *this;   // return the object on which the function was called
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs; // copy data members from lhs into sum
    sum.combine(rhs);  // add data members from rhs into sum
    return sum;
}

std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}

// remember to use Sales_data:: when out of class body
inline double Sales_data::avg_price() const
{
    return units_sold ? revenue / units_sold : 0;
}

// Lines 73-84 are a skeleton for taking a text file argument once the programme is compiled
// e.g. ./myProgramme 8.6.txt
int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: 8.6.txt" << std::endl;
        return -3;
    }
    
    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return -2;
    }
    
    // replace std::cin with input to read from file instead of user input 
    Sales_data total;
    // if (read(std::cin, total)) {
    if (read(input, total)) {
        Sales_data trans;
        // while(read(std::cin, trans)) {
        while(read(input, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(std::cout, total) << std::endl;
                total = trans;
            }
        }
        print(std::cout, total) << std::endl;
    } else {
        std::cerr << "No data?" << std::endl;
    }
    
    return 0;
}
