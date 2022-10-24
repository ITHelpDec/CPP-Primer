// Exercise 15.15:
/*
 Rewrite the class representing a limited discount strategy, which you wrote for the exercises in § 15.2.2 (p. 601), to inherit from Disc_quote.
 
 >> Did this in last exercise
*/

#include <iostream>
#include <string>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) { }
    
    std::string isbn() const { return bookNo; }
    
    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const;
    
    virtual ~Quote() = default;
    
private:
    std::string bookNo;
protected:
    double price = 19.99;
};

// class to hold the discount rate and quantity
// derived classes will implement pricing strategies using these data
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc) { }
    
    double net_price(std::size_t) const = 0;
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

// the discount kicks in when a specified number of copies of the same book are sold
// the discount is expressed as a fraction to use to replace the normal price
class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price , std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
    
    double net_price(std::size_t) const override;
    void debug() const override;
    
    // no private sub-members this time round
};

//class Limited_discount : public Quote {
class Limited_discount : public Disc_quote {
public:
    Limited_discount() = default;
    
    // Limited_discount(const std::string &book, double p, std::size_t max, double disc) : Quote(book, p), max_qty(max), discount(disc) { }
    Limited_discount(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }

    double net_price(std::size_t) const override;
    void debug() const override;

    // no private sub-members here either
};

double Bulk_quote::net_price(std::size_t cnt) const
{
    // if (cnt >= min_qty)
    if (cnt >= quantity)
        return cnt * (1 - discount) * price;
    else
        return cnt * price;
}

double Limited_discount::net_price(std::size_t n) const
{
// if (n > max_qty)
if (n > quantity)
    // return (max_qty * price * (1 - discount)) + ((n - max_qty) * price);
    return (quantity * price * (1 - discount)) + ((n - quantity) * price);
else
    return n * price * (1 -discount);
}

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    
    os << "ISBN: " << item.isbn() << " // # sold: " << n << " // total due: " << ret << std::endl;
    return ret;
}

void Quote::debug() const { std::cout << "ISBN: " << Quote::isbn() << ", price: " << price << std::endl; }

void Bulk_quote::debug() const
// { std::cout << "ISBN: " << isbn() << ", price: " << price << ", min_qty: " << min_qty << ", discount: " << discount << std::endl; }
{ std::cout << "ISBN: " << isbn() << ", price: " << price << ", min_qty: " << quantity << ", discount: " << discount << std::endl; }

void Limited_discount::debug() const
// { std::cout << "ISBN: " << isbn() << ", price: " << price << ", max_qty: " << max_qty << ", discount: " << discount << std::endl; }
{ std::cout << "ISBN: " << isbn() << ", price: " << price << ", max_qty: " << quantity << ", discount: " << discount << std::endl; }

void print_debug(std::ostream &os, const Quote &item) { item.debug(); }

int main()
{
    Quote basic("123-456-789", 19.99);
    Bulk_quote bulk("123-456-789", 19.99, 15, .25);
    Limited_discount limited("123-456-789", 19.99, 10, .5);
    
    std::cout << "Printing totals...\n";
    print_total(std::cout, basic, 20);
    print_total(std::cout, bulk, 20);
    print_total(std::cout, limited, 20);
    
    std::cout << "\nPrinting members with debug()...\n";
    print_debug(std::cout, basic);
    print_debug(std::cout, bulk);
    print_debug(std::cout, limited);
    
    return 0;
}
