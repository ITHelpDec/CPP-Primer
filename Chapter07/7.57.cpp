// Exercise 7.57
/*
 Write your own version of the Account class.
 */

#include <iostream>
#include <string>

class Account {
    // create friend member to output account owner and balance
    // defined outside of class body
    friend std::ostream &print(std::ostream&, const Account&);
public:
    Account() = default;
    // Account() : Account("", 0.0) {} doesn't seem to work?
    
    // create another blank constructor
    Account(std::string &o, double &a) : owner(o), amount(a)
    {
        std::cout << "2 called" << std::endl;
    }
    
    // function to calculate yearly return (void, so no return)
    void calculate() { amount += amount * interestRate; }
    
    
    static double rate() { return interestRate; }
    static void rate(double);   // body of object defined outside of class
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
    
    static constexpr int period = 30;   // period is a constant expression
    double daily_tbl[period];
};

std::ostream &print(std::ostream &os, const Account &a)
{
    os << a.owner << " " << a.amount << " " << a.daily_tbl[Account::period-1] << std::endl;
    return os;
}

// no need to re-declare as static outside of class body
void Account::rate(double newRate)
{
    interestRate = newRate;
}

// define and initialise a static class member
double Account::interestRate = initRate();

double Account::initRate()
{
    return 0.029;
}

// definition of a static member with no initialiser
constexpr int Account::period;

int main()
{
    double r;
    r = Account::rate(); // access a static member using scope operator
    
    std::string person = "John";
    double balance = 213.34;
    Account ac1(person,balance);
    print(std::cout, ac1);
    Account *ac2 = &ac1;
    print(std::cout, *ac2);
    
    // the following code will not work because I can't declare a constructor similar to...
    // Account() : Account("", 0.0) {}
    // Account ac3("Jimmy", 314.45);
    // not sure why...
    
    
    // equivalent ways to call the static number rate function
    r = ac1.rate();     // through an Account object or reference
    std::cout << r << std::endl;
    r = ac2->rate();    // through a pointer to an Account object
    std::cout << r << std::endl;
    
    return 0;
}
