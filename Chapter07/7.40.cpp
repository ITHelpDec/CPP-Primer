// Exercise 7.40
/*
 Choose one of the following abstractions (or an abstraction of your own choosing).
 Determine what data are needed in the class.
 Provide an appropriate set of constructors.
 Explain your decisions.
 
 (a) Book
 (b) Date
 (c) Employee
 (d) Vehicle
 (e) Object
 (f) Tree
 */

// (c) Employee

#include <iostream>
#include <string>

class Employee {
    friend std::ostream &print(std::ostream&, const Employee&);
public:
    // (1) blank constructor for initialisation
    Employee(std::string n, std::string r, unsigned no, unsigned sal) : employeeName(n), jobRole(r), employeeNo(no), salary(sal) {}
    
    // (2) zero'd construcor
    Employee() : Employee("", "", 0, 0) {}
    
    // (3) just name constructor
    Employee(std::string n) : Employee(n, "", 0, 0) {}
    
    // (3) just name constructor
    Employee(std::string n, std::string j) : Employee(n, j, 0, 0) {}
private:
    std::string employeeName = "";
    std::string jobRole = "";   // constructors become difficult with multiple values of similar type
    unsigned employeeNo = 0;
    unsigned salary = 0;
};

std::ostream &print(std::ostream &os, const Employee &e)
{
    os << e.employeeName << " " << e.jobRole << " " << e.employeeNo << " " << e.salary << std::endl;
    return os;
}

int main()
{
    Employee e1("John", "Progammer");  // just an example
    print(std::cout, e1);
    return 0;
}
