// Exercise 14.06:
/*
 Define an output operator for your Sales_data class.
 
 >> Already did this as part of 14.02
*/

#include <iostream>
#include <string>

class Sales_data {
    // recommendations were made to classify std::istream and std::ostream as friends (not member functions)
    // we have been doing this with print functions for a while now, so it shouldn't be a surprise
    friend std::istream& operator>>(std::istream&, Sales_data&);
    friend std::ostream& operator<<(std::ostream&, const Sales_data&);
public:
    // default constructor
    Sales_data() = default;
    
    // rvalue reference constructor
    Sales_data(std::string &&bn, std::size_t &&us, double &&r) : bookNo(bn), units_sold(us), revenue(r)
    { std::cout << "(rvalue reference used)" << std::endl; }
    
    // lvalue reference constructor
    Sales_data(const std::string &bn, const std::size_t &us, const double &r) : bookNo(bn), units_sold(us), revenue(r)
    { std::cout << "(lvalue reference used)" << std::endl; }
    
    // + and += operators
    Sales_data& operator+(const Sales_data&);
    Sales_data& operator+=(const Sales_data&);
    
    std::string isbn() { return bookNo; }
    double avg_price() const { return revenue / units_sold; }
    
private:
    std::string bookNo;
    std::size_t units_sold = 0;
    double revenue = 0.0;
};

// friend input funciton
// do not use const Sales_data or you will not be able to amend input
std::istream& operator>>(std::istream &is, Sales_data &in)
{
    double price = 0;
    is >> in.bookNo >> in.units_sold >> price;
    in.revenue = price * in.units_sold;
    return is;
}

// friend output function
std::ostream& operator<<(std::ostream &os, const Sales_data &out)
{
    double price = 0;
    os << out.bookNo << " " << out.units_sold << " £" << out.avg_price();
    return os;;
}

// member operators for addition and compound-assignment
Sales_data& Sales_data::operator+(const Sales_data &rhs) { return *this + rhs; }
Sales_data& Sales_data::operator+=(const Sales_data &rhs) { return *this += rhs;}

// have updated example from pg 255 with new operators
// old code in comments; updated code below that
// this makes the code look much cleaner
void ret_Total()
{
    Sales_data total;
    // if (read(std::cin, total)) {
    if (std::cin >> total) {
        Sales_data trans;
        // while (read(std::cin, trans)) {
        while(std::cin >> trans) {
            if (total.isbn() == trans.isbn())
                // total.combine(trans);
                total + trans;
            else {
                // print(std::cout, total) << std::endl;
                std::cout << total << std::endl;
                total = trans;
            }
        }
        // print(std::cout, total) << std::endl;
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
    
    // ret_Total();;

    return 0;
}
