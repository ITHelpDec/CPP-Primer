// Exercise 15.07:
/*
 Define a class that implements a limited discount strategy, which applies a discount to books purchased up to a given limit.
 If the number of copies exceeds that limit, the normal price applies to those purchased beyond the limit.
*/

#include <iostream>
#include <string>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    
    std::string isbn() const { return bookNo; }
    
    virtual double net_price(std::size_t n) const { return n * price; }
    
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
    
private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= min_qty)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

// Limited_discount class
class Limited_discount : public Quote {
public:
    Limited_discount() = default;
    Limited_discount(const std::string &book, double p, std::size_t max, double disc) : Quote(book, p), max_qty(max), discount(disc) { }
    
    double net_price(std::size_t) const override;
    
private:
    std::size_t max_qty;
    double discount;
};

// Limited_discount's own net_price function
double Limited_discount::net_price(std::size_t n) const
{
    if (n > max_qty)
        // "discounted" + "undiscounted leftovers"
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

int main()
{
    Quote basic("123-456-789", 19.99);
    Bulk_quote bulk("123-456-789", 19.99, 15, .25);
    
    print_total(std::cout << "basic: ", basic, 20);
    print_total(std::cout << "bulk:  ", bulk, 20);
    
    // tests for limited_discount run
    Limited_discount limit("123-456-789", 19.99, 10, .50);
    print_total(std::cout << "limit: ", limit, 10);
    print_total(std::cout << "limit: ", limit, 12);
    
    return 0;
}

