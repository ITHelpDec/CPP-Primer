// Exercise 15.03:
/*
 Define your own versions of the Quote class and the print_total function.
 
 // Dynamic binding is very clever
*/

#include <iostream>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    
    std::string isbn() const { return bookNo; }
    
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const { return n * price; }
    
    // dynamic binding for the destructor
    virtual ~Quote() = default;
    
private:
    std::string bookNo;
protected:
    double price = 19.99;
};

// Bulk_quote inherits from Quote
class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;
    // use Quote() constructor (public) instead of creating new private / protected members
    Bulk_quote(const std::string &book, double sales_price) : Quote(book, sales_price) { }
    
    // tweak net_price() to include discount
    double net_price(std::size_t n) const override { return price * n * discount; }
private:
    double discount = 0.75;
};

// calculate and print the price for the given number of copies, applying any discounts
double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    // depending on the type of the object bound to the item parameter
    // calls either Quote::net_price or Bulk_quote::net_price
    double ret = item.net_price(n);
    
    os << "ISBN: " << item.isbn() << " // # sold: " << n << " // total due: " << ret << std::endl;
    return ret;
}

int main()
{
    Quote basic("123-456-789", 19.99);
    Bulk_quote bulk("123-456-789", 19.99);
    
    print_total(std::cout, basic, 20);
    print_total(std::cout, bulk, 20);
    
    return 0;
}
