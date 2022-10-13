// Exercise 14.08
/*
 Define an output operator for the class you chose in exercise 7.40 from
*/

#include <iostream>
#include <string>

class Vehicle {
    // freidn output operator
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

// friend output operator
std::ostream &operator<<(std::ostream &os, const Vehicle &car)
{
    os << (car.ignition ? "on" : "off") << " " << car.gear << " " << car.colour;
    return os;
}

int main()
{
    Vehicle m3 = { "black" };
    
    std::cout << "Outputting members of m3: " << m3 << std::endl;
    
    return 0;
}
