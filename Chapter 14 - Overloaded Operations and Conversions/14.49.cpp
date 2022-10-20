// Exercise 14.49:
/*
 Regardless of whether it is a good idea to do so (lol), define a conversion to bool for the class from the previous exercise.

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
    Employee(std::string n, std::string r, unsigned no, unsigned sal) : employee_name(n), job_role(r), employee_no(no), salary(sal) {}
    Employee() : Employee("", "", 0, 0) {}
    Employee(std::string n) : Employee(n, "", 0, 0) {}
    Employee(std::string n, std::string j) : Employee(n, j, 0, 0) {}
    
    // no idea why this would be useful
    explicit operator bool() const { return employee_no ? true : false; }
private:
    std::string employee_name = "";
    std::string job_role = "";
    unsigned employee_no = 0;
    unsigned salary = 0;
};

std::ostream &print(std::ostream &os, const Employee &e)
{
    os << e.employee_name << " " << e.job_role << " " << e.employee_no << " " << e.salary << std::endl;
    return os;
}

int main()
{
    Employee e1("John", "Progammer");
    print(std::cout, e1);
    return 0;
}
