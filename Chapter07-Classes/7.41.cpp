// Exercise 7.41
/*
 Rewrite your own version of the Sales_data class to use delegating constructors.
 Add a statement to the body of each of the constructors that prints a message whenever it is executed.
 Write declarations to construct a Sales_data object in every way possible.
 Study the output until you are certain you understand the order of execution among delegating constructors.
 */

#include <iostream>
#include <string>

class Sales_data {
    // friend declarations for non-member Sales_data operations added
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    
public:
   // non-delegating constructor initialises members from corresponding arguments
    Sales_data(std::string s, unsigned cnt, double price) : bookNo(s), units_sold(cnt), revenue(cnt*price)
    {
        std::cout << "Sales_data(std::string s, unsigned cnt, double price) : bookNo(s), units_sold(cnt), revenue(cnt*price) has been called." << std::endl;
    }
    // remaining construction all delegate to another constructor
    Sales_data() : Sales_data("", 0, 0)
    {
        std::cout << "Sales_data() : Sales_data("", 0, 0) has been called." << std::endl;
    }
    Sales_data(std::string s) : Sales_data(s, 0, 0)
    {
        std::cout << "Sales_data(std::string s) : Sales_data(s, 0, 0) has been called." << std::endl;
    }
    Sales_data(std::istream &is) : Sales_data() {
        std::cout << "Sales_data(std::istream &is) : Sales_data() has been called." << std::endl;
        read(is, *this);
    }
    
    Sales_data &combine(const Sales_data&);
    std::string isbn() const { return bookNo; }

private:
    double avg_price() const;   // inlined outside of the class body
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    
    
};

Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

Sales_data &Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;   // add the members of rhs into
    revenue += rhs.revenue;         // the members of this object
    return *this;   // return the object on which the function was called
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

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs; // copy data members from lhs into sum
    sum.combine(rhs);  // add data members from rhs into sum
    return sum;
}

// remember to use Sales_data:: when out of class body
inline double Sales_data::avg_price() const
{
    return units_sold ? revenue / units_sold : 0;
}


int main()
{
    // this calls two class member functions
    // uninitialised and then initialised to blanks
    Sales_data item1;
    print(std::cout, item1);    // prints blanks
    
    // both string constructors called
    Sales_data item2("0-135-161797");
    print(std::cout, item2);    // prints ISBN and blanks
    
    // only constructor called
    Sales_data item3("0-135-161797", 2, 45.75);
    print(std::cout, item3);    // prints ISBN, quantity, revenue and average price
    
    // 3 constructors called – uninitialised, blanks and cin
    Sales_data item4(std::cin);
    print(std::cout, item4);    // prints user input
    
    return 0;
}
