#include "Sales_data.hpp"

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
        } std::cout << total << std::endl;
    } else { std::cerr << "No data?!" << std::endl; }
}

int main()
{
    Sales_data sd = { "123-456-789", 2, 49.98 };
    
    // returns "49.98"
    std::cout << static_cast<double>(sd) << std::endl;
    
    // returns "123-456-789"
    std::cout << static_cast<std::string>(sd) << std::endl;
    
    return 0;
}
