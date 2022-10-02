// Exercise 13.18:
/*
 Define an Employee class that contains an employee name and a unique employee identifier.
 Give the class a default constructor and a constructor that takes a string representing the employee’s name.
 Each constructor should generate a unique ID by incrementing a static data member.
 */

#include <string>
#include <iostream>

class Employee {
public:
    Employee() : id(++id_count) {std::cout << "E()" << std::endl; }
    explicit Employee(const std::string &s) : name(s), id(++id_count) { std::cout << "E(s)" << std::endl; }
    
    // can also do the following in C++17 to combine lines 18 and 29
    // static inline std::size_t Employee::id_count = 0;
    static std::size_t id_count;
    
    
    const std::string &getname() const { return name; }
    const std::size_t &getid() const { return id; }
    
private:
    std::string name;
    std::size_t id;
};

std::size_t Employee::id_count = 0;

int main()
{
    Employee e1;
    std::cout << "e1: name = \"" << e1.getname() << "\", id = #" << e1.getid() << std::endl;
    
    Employee e2("manbearpig");
    std::cout << "e2: name = \"" << e2.getname() << "\", id = #" << e2.getid() << std::endl;
    
    return 0;
}
