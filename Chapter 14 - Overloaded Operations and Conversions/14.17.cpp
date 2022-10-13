// Exercise 14.17:
/*
 Should the class you chose for exercise 7.40 from § 7.5.1 (p. 291) define the equality operators?
 If so, implement them.
 If not, explain why not.
 
 >> Could do equality operators
*/

#include <iostream>
#include <string>

class Vehicle {
    // == and != operators
    friend bool operator==(const Vehicle&, const Vehicle&);
    friend bool operator!=(const Vehicle&, const Vehicle&);
    
    friend std::istream &operator>>(std::istream&, Vehicle&);
    friend std::ostream &operator<<(std::ostream&, const Vehicle&);
    
public:
    Vehicle() = default;
    
    Vehicle(std::string &&col) : ignition(), gear(1), colour(col) { }
    
    void turn_on() { ignition = true; }
    void turn_off() { ignition = false; }
    std::string state() { return (ignition ? "on" : "off"); }
    std::size_t current_gear() { return gear; }
    void shift_up();
    void shift_down();
    
private:
    bool ignition = false;
    std::size_t gear = 1;
    std::string colour;
};

void Vehicle::shift_up()
{
    if (gear > 5) {
        std::cerr << "No more gears!" << std::endl;
        return;
    }
    std::cout << "Changing from gear " << gear << " to gear " << ++gear << "..." << std::endl;
}

void Vehicle::shift_down()
{
    if (gear < 2) {
        std::cerr << "No more gears!" << std::endl;
        return;
    }
    std::cout << "Changing from gear " << gear << " to gear " << --gear << "..." << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Vehicle &car)
{
    os << (car.ignition ? "on" : "off") << " " << car.gear << " " << car.colour;
    return os;
}

std::istream &operator>>(std::istream &is, Vehicle &car)
{
    if (is)
        // check that input succeeded
        is >> car.ignition >> car.gear >> car.colour;
    else
        // if input fails, give Vehicle default state
        car = Vehicle();
    return is;
}

bool operator==(const Vehicle &lhs, const Vehicle &rhs)
{
    return lhs.ignition == rhs.ignition &&
    lhs.gear == rhs.gear &&
    lhs.colour == rhs.colour;
}

bool operator!=(const Vehicle &lhs, const Vehicle &rhs)
{
    return !(lhs == rhs);
}

int main()
{
    std::cout << "Creating two identical cars...\n";
    Vehicle m3_1 = { "black" };
    Vehicle m3_2 = { "red" };
    
    std::cout << "Testing to see if the cars are the same...\n";
    std::cout << (m3_1 == m3_1 ? "Same." : "Not the same.") << std::endl;
    
    std::cout << "\nCreating a new car with a different colour...\n";
    Vehicle m3_3 = { "red" };
    
    std::cout << "Testing to see if the cars are the same...\n";
    std::cout << (m3_1 != m3_3 ? "Not the same." : "Same.") << std::endl;
    
    return 0;
}
