// Exercise 15.11:
/*
 Add a virtual debug function to your Quote class hierarchy that displays the data members of the respective classes.
*/

#include <iostream>
#include <string>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    
    std::string isbn() const { return bookNo; }
    
    virtual double net_price(std::size_t n) const { return n * price; }
    
    // virtual base debug() function
    virtual void debug() const;
    
    virtual ~Quote() = default;
    
private:
    std::string bookNo;
protected:
    double price = 19.99;
};

class Bulk_quote : public Quote {
    
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double p , std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) { }
    
    double net_price(std::size_t n) const override;
    
    // derived-from-base debug() function
    void debug() const override;
    
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};
 
 class Limited_discount : public Quote {
 public:
     Limited_discount() = default;
     Limited_discount(const std::string &book, double p, std::size_t max, double disc) : Quote(book, p), max_qty(max), discount(disc) { }
     
     double net_price(std::size_t) const override;
     
     // derived-from-base debug() function
     void debug() const override;
     
 private:
     std::size_t max_qty;
     double discount;
 };

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

double Limited_discount::net_price(std::size_t n) const
{
if (n > max_qty)
    return (max_qty * price * (1 - discount)) + ((n - max_qty) * price);
else
    return n * price * (1 -discount);
}

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    
    os << "ISBN: " << item.isbn() << " // # sold: " << n << " // total due: " << ret << std::endl;
    return ret;
}

// base debug() similar to net_price() functions
void Quote::debug() const { std::cout << "ISBN: " << isbn() << ", price: " << price << std::endl; }

// derived-from-base debug()
void Bulk_quote::debug() const
{ std::cout << "ISBN: " << isbn() << ", price: " << price << ", min_qty: " << min_qty << ", discount: " << discount << std::endl; }

// another derived-from-base debug()
void Limited_discount::debug() const
{ std::cout << "ISBN: " << isbn() << ", price: " << price << ", max_qty: " << max_qty << ", discount: " << discount << std::endl; }

// print_debug() function similar to print_total()
void print_debug(std::ostream &os, const Quote &item) { item.debug(); }

int main()
{
    Quote basic("123-456-789", 19.99);
    Bulk_quote bulk("123-456-789", 19.99, 15, .25);
    Limited_discount limited("123-456-789", 19.99, 12, .5);
    
    // is this too complicated? I tried to replicate the print_total() structure
    print_debug(std::cout, basic);
    print_debug(std::cout, bulk);
    print_debug(std::cout, limited);
    
    // can also call as below (maybe this is slightly easier, but less dynamic than the print_total() function?)
    basic.debug();
    bulk.debug();
    limited.debug();
    
    return 0;
}
