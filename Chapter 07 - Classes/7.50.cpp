// Exercise 7.50:
/*
 Determine whether any of your Person class constructors should be explicit.
 */

#include <iostream>
#include <string>

class Person {
    friend std::istream &read(std::istream&, Person&);
    // friend std::ostream print(std::ostream, const Person&);

public:
    Person() = default; // default initialiser
    // Person(const std::string &s) : name(s) {} can be made explicit
    explicit Person(const std::string &s) : name(s) {}
    Person(const std::string &s1, const std::string &s2) : name(s1), address(s2) {}
    // Person(istream&); can be made explciit
    explicit Person(std::istream&);
    
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }

private:
    std::string name;
    std::string address;
};

std::istream &read(std::istream &is, Person &rhs)
{
    is >> rhs.name >> rhs.address;
    return is;
}

std::ostream &print(std::ostream &os, const Person &rhs)
{
    os << rhs.getName() << " " << rhs.getAddress();
    return os;
}

Person::Person(std::istream &is)
{
    read(is, *this);
}

int main()
{
    Person p1("John", "Portugal");
    print(std::cout, p1);
    
    Person p2;
    read(std::cin, p2);
    print(std::cout, p2);

    return 0;
}
