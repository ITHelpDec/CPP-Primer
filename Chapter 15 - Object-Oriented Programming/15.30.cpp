// Exercise 15.30:
/*
 Write your own version of the Basket class and use it to compute prices for the same transactions as you used in the previous exercises.
*/

// Quote.hpp

#ifndef Quote_hpp
#define Quote_hpp

#include <string>
#include <iostream>
#include <string>
#include <utility>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price)
    { /* std::cout << "Quote(const std::string&, double) called." << std::endl; */ }
    
    Quote(const Quote&);
    Quote& operator=(const Quote&);
    
    Quote(Quote&&) noexcept;
    Quote& operator=(Quote&&) noexcept;

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const;
    
    // virtual function to return a dynamically-allocated copy of itself
    // these members use reference qualifiers
    virtual Quote* clone() const & { return new Quote(*this); }
    virtual Quote* clone() && noexcept { return new Quote(std::move(*this)); }
    
    virtual ~Quote() { /* std::cout << "~Quote() called." << std::endl; */ }

private:
    std::string bookNo;
protected:
    double price = 19.99;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc)
    { /* std::cout << "Disc_quote(const std::string&, double, std::size_t, double) called." << std::endl; */ }
    
    Disc_quote(const Disc_quote&);
    Disc_quote& operator=(const Disc_quote&);
    
    Disc_quote(Disc_quote&&) noexcept;
    Disc_quote& operator=(Disc_quote&&) noexcept;
    
    ~Disc_quote() { /* std::cout << "~Disc_quote() called." << std::endl; }*/ }
    
    double net_price(std::size_t) const = 0;

    std::pair<std::size_t, double> discount_policy() const { return { quantity, discount }; }
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;
    
    Bulk_quote(const Bulk_quote&);
    Bulk_quote& operator=(const Bulk_quote&);
    
    Bulk_quote(Bulk_quote&&) noexcept;
    Bulk_quote& operator=(Bulk_quote&&) noexcept;
    
    ~Bulk_quote() { /* std::cout << "~Bulk_quote() called." << std::endl; */ };
    
    double net_price(std::size_t) const override;
    void debug() const override;
    
    // virtual clone funcitons as in base class
    Bulk_quote* clone() const & override { return new Bulk_quote(*this); }
    Bulk_quote* clone() && noexcept override { return new Bulk_quote(std::move(*this)); }
};

class Limited_discount : public Disc_quote {
public:
    Limited_discount() = default;
    Limited_discount(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc)
    { /* std::cout << "Limited_discount(const std::string&, double, std::size_t, double) called." << std::endl; */ }
    
    Limited_discount(const Limited_discount&);
    Limited_discount& operator=(const Limited_discount&);
    
    Limited_discount(Limited_discount&&);
    Limited_discount& operator=(Limited_discount&&);
    
    ~Limited_discount() { /* std::cout << "~Limited_discount() called." << std::endl; */ }

    double net_price(std::size_t) const override;
    void debug() const override;
    
    // final virtual functions - remember: no const for && moves
    Limited_discount* clone() const & override { return new Limited_discount(*this); }
    Limited_discount* clone() && noexcept override { return new Limited_discount(std::move(*this)); }
};

#endif /* Quote_hpp */

// Basket.hpp


#ifndef Basket_hpp
#define Basket_hpp

#include "Quote.hpp"

#include <set>

class Basket {
public:
    // Basket uses synthesised default constructor and copy-control members
    // void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
    
    // copy constructor
    void add_item(const Quote &sale)
    { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    
    // move constructor
    void add_item(Quote &&sale)
    { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
    
    double total_receipt(std::ostream&) const;
    
private:
    // function to compare shared_ptrs needed by the multiset member
    // we do this because std::shared_ptr has no less-than operator ("<")
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    
    // multiset to hold multiple Quotes, orderde by the compare the member
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items { compare };
};

#endif /* Basket_hpp */

// Quote.cpp

#include "Quote.hpp"
#include "Basket.hpp"

Quote::Quote(const Quote &q) : bookNo(q.bookNo), price(q.price)
{ /*std::cout << "Quote(const Quote&) called." << std::endl; */ }

Quote& Quote::operator=(const Quote &rhs)
{
    bookNo = rhs.bookNo;
    price = rhs.price;
    // std::cout << "Quote& Quote::operator=(const Quote &rhs) called." << std::endl;
    return *this;
}

Quote::Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price))
{
    q.bookNo = q.price = NULL;
    // std::cout << "Quote::Quote(Quote &&q) noexcept called." << std::endl;
}

Quote& Quote::operator=(Quote &&rhs) noexcept
{
    if (this != &rhs) {
        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
        bookNo = price = NULL;
    }
    // std::cout << "Quote& Quote::operator=(Quote &&rhs) noexcept called." << std::endl;
    return *this;
}

Disc_quote::Disc_quote(const Disc_quote &d) : Quote(d), quantity(d.quantity), discount(d.discount)
{ /* std::cout << "Disc_quote::Disc_quote(const Disc_quote &d) : Quote(d) called." << std::endl; */ }

Disc_quote& Disc_quote::operator=(const Disc_quote &rhs)
{
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    // std::cout << "Disc_quote& Disc_quote::operator=(const Disc_quote &rhs) called." << std::endl;
    return *this;
}

Disc_quote::Disc_quote(Disc_quote &&d) noexcept : Quote(std::move(d)), quantity(std::move(d.quantity)), discount(std::move(d.discount))
{
    d.price = d.quantity = d.discount = NULL;
    // std::cout << "Disc_quote::Disc_quote(Disc_quote &&d) noexcept : Quote(std::move(d)) called." << std::endl;
}

Disc_quote& Disc_quote::operator=(Disc_quote &&rhs) noexcept
{
    if (this != &rhs) {
        Quote::operator=(std::move(rhs));
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    // std::cout << "Disc_quote& Disc_quote::operator=(Disc_quote&&) noexcept called." << std::endl;
    return *this;
}

Bulk_quote::Bulk_quote(const Bulk_quote &b) : Disc_quote(b)
{ /* std::cout << "Bulk_quote::Bulk_quote(const Bulk_quote &b) : Disc_quote(b) called." << std::endl; */ }

Bulk_quote& Bulk_quote::operator=(const Bulk_quote &rhs)
{
    Disc_quote::operator=(rhs);
    // std::cout << "Bulk_quote& Bulk_quote::operator=(const Bulk_quote &rhs) called." << std::endl;
    return *this;
}

Bulk_quote::Bulk_quote(Bulk_quote &&b) noexcept : Disc_quote(std::move(b))
{
    b.price = b.quantity = b.quantity = NULL;
    // std::cout << "Bulk_quote::Bulk_quote(Bulk_quote &&b) noexcept : Disc_quote(std::move(b)) called." << std::endl;
}

Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs) noexcept
{
    if (this != &rhs) {
        Disc_quote::operator=(std::move(rhs));
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    // std::cout << "Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs) noexcept called." << std::endl;
    return *this;
}

Limited_discount::Limited_discount(const Limited_discount &l) : Disc_quote(l)
{ /* std::cout << "Limited_discount::Limited_discount(const Limited_discount &l) : Disc_quote(l) called." << std::endl; */ }

Limited_discount& Limited_discount::operator=(const Limited_discount &rhs)
{
    Disc_quote::operator=(rhs);
    // std::cout << "Limited_discount& Limited_discount::operator=(const Limited_discount &rhs) called." << std::endl;
    return *this;
}

Limited_discount::Limited_discount(Limited_discount &&l) : Disc_quote(std::move(l))
{
    l.price = l.quantity = l.discount = NULL;
    // std::cout << "Limited_discount::Limited_discount(Limited_discount &&l) : Disc_quote(std::move(l)) called." << std::endl;
}

Limited_discount& Limited_discount::operator=(Limited_discount &&rhs)
{
    if (this != &rhs) {
        Disc_quote::operator=(std::move(rhs));
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    // std::cout << "Limited_discount& Limited_discount::operator=(Limited_discount &&rhs) called." << std::endl;
    return *this;
}

double Bulk_quote::net_price(std::size_t cnt) const
{
    if (cnt >= quantity) { return cnt * (1 - discount) * price; }
    else { return cnt * price; }
}

double Limited_discount::net_price(std::size_t n) const
{
    if (n > quantity) { return (quantity * price * (1 - discount)) + ((n - quantity) * price); }
    else { return n * price * (1 -discount); }
}

double print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " // # sold: " << n << " // total due: " << ret << std::endl;
    return ret;
}

void Quote::debug() const { /* std::cout << "ISBN: " << Quote::isbn() << ", price: " << price << std::endl; */ }

void Bulk_quote::debug() const
{ /* std::cout << "ISBN: " << isbn() << ", price: " << price << ", min_qty: " << quantity << ", discount: " << discount << std::endl; */ }

void Limited_discount::debug() const
{ /* std::cout << "ISBN: " << isbn() << ", price: " << price << ", max_qty: " << quantity << ", discount: " << discount << std::endl; */ }

void print_debug(std::ostream &os, const Quote &item) { item.debug(); }

double Basket::total_receipt(std::ostream &os) const
{
    // holding the running total
    double sum = 0.0;
    
    // "iter" refers to the first element in a batch of elements with the same ISBN
    // upper_bound returns an iterator to the element just past the end of that batch
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        // we know there's at least one element with this key in the Basket
        // print the line item for this book
        sum += print_total(os, **iter, items.count(*iter));
    }
    
    // print the final overall total
    os << "Total Sale: " << sum << std::endl;
    
    return sum;
}

int main()
{
    Quote quote("123-456-789", 20.00);
    Bulk_quote bulk("123-456-789", 20.00, 10, .25);
    Limited_discount limited("123-456-789", 20, 3, .25);
    
    Basket quote_basket;
    Basket bulk_basket;
    Basket limited_basket;
    
    std::cout << ".:. quote_basket .:.\n";
    for (auto i = 0; i != 10; ++i)
    { quote_basket.add_item(Quote("123-456-789", 20.00)); }
    quote_basket.total_receipt(std::cout);
    
    std::cout << "\n.:. bulk_basket .:.\n";
    for (auto i = 0; i != 10; ++i)
    { bulk_basket.add_item(Bulk_quote("123-456-789", 20.00, 10, .25)); }
    bulk_basket.total_receipt(std::cout);

    std::cout << "\n.:. limited_basket .:.\n";
    for (auto i = 0; i != 10; ++i)
    { limited_basket.add_item(Limited_discount("123-456-789", 20, 3, .25)); }
    limited_basket.total_receipt(std::cout);
    
    std::cout << "\n.:. total_basket .:.\n";
    Basket total_basket;
    for (auto i = 0; i != 10; ++i) {
        total_basket.add_item(Quote("123-456-789", 20.00));
        total_basket.add_item(Bulk_quote("123-456-789", 20.00, 10, .25));
        total_basket.add_item(Limited_discount("123-456-789", 20, 3, .25));
    } total_basket.total_receipt(std::cout);
    
    // unexpected behaviour for total_basket.total_receipt() - resorts to Quote::net_total
    // i'd have thought total sale would be 200 + 150 + 185 = 535, not 600
    
    return 0;
}
