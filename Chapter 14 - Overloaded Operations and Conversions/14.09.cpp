// Exercise 14.09:
/*
 Define an input operator for your Sales_data class.
*/

#include <iostream>
#include <string>

class Vehicle {
    // friend input operator
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

int main()
{
    Vehicle m3 = { "black" };
    
    std::cout << "Outputting members of m3: " << m3 << std::endl;
    
    Vehicle m4;
    
    std::cout << "Input details of car (engine, gear, colour): ";
    std::cin >> m4;
    
    // 1 5 yellow
    std::cout << "Outputting members of m4: " << m4 << std::endl;
    
    return 0;
}
