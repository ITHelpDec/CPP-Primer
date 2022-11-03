// Exercise 15.26:
/*
 Define the Quote and Bulk_quote copy-control members to do the same job as the synthesized versions.
 Give them and the other constructors print statements that identify which function is running.
 Write programs using these classes and predict what objects will be created and destroyed.
 Compare your predictions with the output and continue experimenting until your predictions are reliably correct.
*/

// Quote.hpp

#ifndef Quote_hpp
#define Quote_hpp

#include <iostream>
#include <string>
#include <utility>

class Quote {
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price)
    { std::cout << "Quote(const std::string&, double) called." << std::endl; }
    
    // copy and copy-assignment
    Quote(const Quote&);
    Quote& operator=(const Quote&);
    
    // move and move-assignment
    Quote(Quote&&) noexcept;
    Quote& operator=(Quote&&) noexcept;

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }
    virtual void debug() const;
    
    // destructor
    virtual ~Quote() { std::cout << "~Quote() called." << std::endl; }

private:
    std::string bookNo;
protected:
    double price = 19.99;
};

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string &book, double price, std::size_t qty, double disc) : Quote(book, price), quantity(qty), discount(disc)
    { std::cout << "Disc_quote(const std::string&, double, std::size_t, double) called." << std::endl; }
    
    // copy and copy assignment - base inheritance defined further down
    Disc_quote(const Disc_quote&);
    Disc_quote& operator=(const Disc_quote&);
    
    // move and move-assignmnet
    Disc_quote(Disc_quote&&) noexcept;
    Disc_quote& operator=(Disc_quote&&) noexcept;
    
    // destructor
    ~Disc_quote() { std::cout << "~Disc_quote() called." << std::endl; };
    
    double net_price(std::size_t) const = 0;

    std::pair<std::size_t, double> discount_policy() const { return { quantity, discount}; }
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string &book, double price , std::size_t qty, double disc) : Disc_quote(book, price, qty, disc)
    { std::cout << "Bulk_quote(const std::string&, double , std::size_t, double) called." << std::endl; }
    
    // copy and copy assignment
    Bulk_quote(const Bulk_quote&);
    Bulk_quote& operator=(const Bulk_quote&);
    
    // move and move-assignment
    Bulk_quote(Bulk_quote&&) noexcept;
    Bulk_quote& operator=(Bulk_quote&&) noexcept;
    
    // destructor
    ~Bulk_quote() { std::cout << "~Bulk_quote() called." << std::endl; };

    double net_price(std::size_t) const override;
    void debug() const override;
};

class Limited_discount : public Disc_quote {
public:
    Limited_discount() = default;
    Limited_discount(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc)
    { std::cout << "Limited_discount(const std::string&, double, std::size_t, double) called." << std::endl; }
    
    // copy and copy-assignment
    Limited_discount(const Limited_discount&);
    Limited_discount& operator=(const Limited_discount&);
    
    // move and move-assignment
    Limited_discount(Limited_discount&&);
    Limited_discount& operator=(Limited_discount&&);
    
    // destructor
    ~Limited_discount() { std::cout << "~Limited_discount() called." << std::endl; }

    double net_price(std::size_t) const override;
    void debug() const override;
};

#endif /* Quote_hpp */

// Quote.cpp

#include "Quote.hpp"

// Quote copy (done)
Quote::Quote(const Quote &q) : bookNo(q.bookNo), price(q.price)
{ std::cout << "Quote(const Quote&) called." << std::endl; }

// Quote copy-assignment (done)
Quote& Quote::operator=(const Quote &rhs)
{
    bookNo = rhs.bookNo;
    price = rhs.price;
    std::cout << "Quote& Quote::operator=(const Quote &rhs) called." << std::endl;
    return *this;
}

// Quote move (done)
Quote::Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price))
{
    q.bookNo = q.price = NULL;
    std::cout << "Quote::Quote(Quote &&q) noexcept called." << std::endl;
}

// Quote move-assignment (done)
Quote& Quote::operator=(Quote &&rhs) noexcept
{
    if (this != &rhs) {
        bookNo = std::move(rhs.bookNo);
        price = std::move(rhs.price);
        bookNo = price = NULL;
    }
    std::cout << "Quote& Quote::operator=(Quote &&rhs) noexcept called." << std::endl;
    return *this;
}

// Disc_quote copy (done)
Disc_quote::Disc_quote(const Disc_quote &d) : Quote(d), quantity(d.quantity), discount(d.discount)
{ std::cout << "Disc_quote::Disc_quote(const Disc_quote &d) : Quote(d) called." << std::endl; }

// Disc_quote copy-assignment (done)
Disc_quote& Disc_quote::operator=(const Disc_quote &rhs)
{
    Quote::operator=(rhs);
    quantity = rhs.quantity;
    discount = rhs.discount;
    std::cout << "Disc_quote& Disc_quote::operator=(const Disc_quote &rhs) called." << std::endl;
    return *this;
}

// Disc_quote move (done)
Disc_quote::Disc_quote(Disc_quote &&d) noexcept : Quote(std::move(d)), quantity(std::move(d.quantity)), discount(std::move(d.discount))
{
    d.price = d.quantity = d.discount = NULL;
    std::cout << "Disc_quote::Disc_quote(Disc_quote &&d) noexcept : Quote(std::move(d)) called." << std::endl;
}

// Disc_quote move-assignmnet (done)
Disc_quote& Disc_quote::operator=(Disc_quote &&rhs) noexcept
{
    if (this != &rhs) {
        Quote::operator=(std::move(rhs));
        quantity = std::move(rhs.quantity);
        discount = std::move(rhs.discount);
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    std::cout << "Disc_quote& Disc_quote::operator=(Disc_quote&&) noexcept called." << std::endl;
    return *this;
}

// Bulk_quote copy (done)
Bulk_quote::Bulk_quote(const Bulk_quote &b) : Disc_quote(b)
{ std::cout << "Bulk_quote::Bulk_quote(const Bulk_quote &b) : Disc_quote(b) called." << std::endl; }

// Bulk_quote copy assignment (done)
Bulk_quote& Bulk_quote::operator=(const Bulk_quote &rhs)
{
    Disc_quote::operator=(rhs);
    std::cout << "Bulk_quote& Bulk_quote::operator=(const Bulk_quote &rhs) called." << std::endl;
    return *this;
}

// Bulk_quote move (undone) (done)
Bulk_quote::Bulk_quote(Bulk_quote &&b) noexcept : Disc_quote(std::move(b))
{
    b.price = b.quantity = b.quantity = NULL;
    std::cout << "Bulk_quote::Bulk_quote(Bulk_quote &&b) noexcept : Disc_quote(std::move(b)) called." << std::endl;
}

// Bulk_quote move-assignment (done)
Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs) noexcept
{
    if (this != &rhs) {
        Disc_quote::operator=(std::move(rhs));
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    std::cout << "Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs) noexcept called." << std::endl;
    return *this;
}

// copy (done)
Limited_discount::Limited_discount(const Limited_discount &l) : Disc_quote(l)
{ std::cout << "Limited_discount::Limited_discount(const Limited_discount &l) : Disc_quote(l) called." << std::endl; }

// copy-assignment (done)
Limited_discount& Limited_discount::operator=(const Limited_discount &rhs)
{
    Disc_quote::operator=(rhs);
    std::cout << "Limited_discount& Limited_discount::operator=(const Limited_discount &rhs) called." << std::endl;
    return *this;
}

// move (done)
Limited_discount::Limited_discount(Limited_discount &&l) : Disc_quote(std::move(l))
{
    l.price = l.quantity = l.discount = NULL;
    std::cout << "Limited_discount::Limited_discount(Limited_discount &&l) : Disc_quote(std::move(l)) called." << std::endl;
}

// move-assignment (done)
Limited_discount& Limited_discount::operator=(Limited_discount &&rhs)
{
    if (this != &rhs) {
        Disc_quote::operator=(std::move(rhs));
        rhs.price = rhs.quantity = rhs.discount = NULL;
    }
    std::cout << "Limited_discount& Limited_discount::operator=(Limited_discount &&rhs) called." << std::endl;
    return *this;
}

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
    std::cout << "Testing constructors...\n";
    Quote basic("123-456-789", 19.99);
    Bulk_quote bulk("123-456-789", 19.99, 15, .25);
    Limited_discount limited("123-456-789", 19.99, 10, .5);
    
    std::cout << "\nTesting copy operators...\n";
    Quote basic_copy(basic);
    Bulk_quote bulk_copy(bulk);
    Limited_discount limited_copy(limited);
    
    std::cout << "\nTesting copy-assignment operator...\n";
    basic_copy = bulk;
    bulk_copy = bulk;
    limited_copy = limited;
    
    std::cout << "\nTesting move operators...\n";
    Quote basic_move(std::move(basic));
    Bulk_quote bulk_move(std::move(bulk));
    Limited_discount limited_move(std::move(limited));
    
    std::cout << "\nTesting move-assignment operators...\n";
    basic_move = { "123-456-789", 19.90 };
    bulk_move = { "123-456-789", 19.99, 15, .25 };
    limited_move = { "123-456-789", 19.99, 10, .5 };
    
    // destructors
    std::cout << "\nTesting destructors...\n";
    
    return 0;
}

