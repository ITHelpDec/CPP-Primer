// Exercise 13.19:
/*
 Does your Employee class need to define its own versions of the copy-control members?
 If so, why? If not, why not? Implement whatever copy-control members you think Employee needs.
 
 >> Yes, in order to copy-assign the name and id's from e2 to e1 – ssee below.
 */

#include <string>
#include <iostream>

class Employee {
public:
    Employee() : id(++id_count) {std::cout << "E()" << std::endl; }
    explicit Employee(const std::string &s) : name(s), id(++id_count) { std::cout << "E(s)" << std::endl; }
    
    // copy constructor
    Employee(const Employee&) : id(++id_count) { std::cout << "E() copy" << std::endl; }
    
    // copy-assign declaration
    Employee& operator=(const Employee&);
    
    static std::size_t id_count;
    
    const std::string &getname() const { return name; }
    const std::size_t &getid() const { return id; }
    
private:
    std::string name;
    std::size_t id;
};

std::size_t Employee::id_count = 0;

Employee& Employee::operator=(const Employee &rhs)
{
    // transfer name and id
    // same person, so surely same id as well, making e1 and e2 duplicate records?
    name = rhs.name;
    id = rhs.id;
    std::cout << "E() copy assign" << std::endl;
    return *this;
}

int main()
{
    Employee e1;
    std::cout << "e1: name = \"" << e1.getname() << "\", id = #" << e1.getid() << std::endl;
    
    Employee e2("John");
    std::cout << "e2: name = \"" << e2.getname() << "\", id = #" << e2.getid() << std::endl;
    
    // copy
    Employee e3 = e2;
    std::cout << "e3: name = \"" << e3.getname() << "\", id = #" << e3.getid() << std::endl;
    
    // copy assign
    e1 = e2;
    std::cout << "e1: name = \"" << e1.getname() << "\", id = #" << e1.getid() << std::endl;
    
    return 0;
}
