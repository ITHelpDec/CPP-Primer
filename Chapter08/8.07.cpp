// Exercise 8.7:
/*
 Revise the bookstore program from the previous section to write its output to a file.
 Pass the name of that file as a second argument to main.
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
    double avg_price() const;
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

int main(int argc, char **argv)
{
    // main will take three arguments
    // ./main
    // 8.07.txt
    // 8.07output.txt
    if (argc < 3) {
        std::cerr << "Reading 8.07.txt..." << std::endl;
        return -3;
    }
    
    // input argument
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file: " << argv[1] << std::endl;
        return -2;
    }
    
    // output argument
    // if file doesn't exist, it will be created, so need need for if (!out) std::cerr
    std::ofstream out(argv[2]);
    
    // replace std::cout with out to write to file instead of console
    Sales_data total;
    if (read(in, total)) {
        Sales_data trans;
        while(read(in, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                // print(std::cout, total) << std::endl;
                print(out, total) << std::endl;
                total = trans;
            }
        }
        // print(std::cout, total) << std::endl;
        print(out, total) << std::endl;
    } else {
        std::cerr << "No data?" << std::endl;
    }
    
    return 0;
}
