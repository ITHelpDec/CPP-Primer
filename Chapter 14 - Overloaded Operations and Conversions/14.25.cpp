// Exercise 14.25:
/*
 Implement any other assignment operators your class should define. Explain which types should be used as operands and why.
 
 >> The ones I've done already will suffice for now
*/

#include <iostream>
#include <string>

class Vehicle {
    friend bool operator<(const Vehicle&, const Vehicle&);
    friend bool operator>(const Vehicle&, const Vehicle&);
    
    friend bool operator<=(const Vehicle&, const Vehicle&);
    friend bool operator>=(const Vehicle&, const Vehicle&);
    
    friend bool operator==(const Vehicle&, const Vehicle&);
    friend bool operator!=(const Vehicle&, const Vehicle&);
    
    friend std::istream &operator>>(std::istream&, Vehicle&);
    friend std::ostream &operator<<(std::ostream&, const Vehicle&);
    
public:
    Vehicle() = default;
    Vehicle(std::string &&col) : ignition(), gear(1), colour(col) { }
    Vehicle(bool &&onoff, std::size_t &&gr, std::string &&col) : ignition(onoff), gear(gr), colour(col) { }
    
    Vehicle& operator=(const Vehicle&);
    Vehicle& operator=(Vehicle&&) noexcept;
    
    void turn_on() { ignition = true; }
    void turn_off() { ignition = false; }
    void shift_up();
    void shift_down();
    
    std::string state() { return (ignition ? "on" : "off"); }
    std::size_t current_gear() { return gear; }
    
private:
    bool ignition = false;
    std::size_t gear = 1;
    std::string colour;
};

void Vehicle::shift_up()
{
    if (gear > 5) { std::cerr << "No more gears!" << std::endl; return; }
    std::cout << "Changing from gear " << gear << " to gear " << ++gear << "..." << std::endl;
}

void Vehicle::shift_down()
{
    if (gear < 2) { std::cerr << "No more gears!" << std::endl; return; }
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

bool operator!=(const Vehicle &lhs, const Vehicle &rhs) { return !(lhs == rhs); }

bool operator<(const Vehicle &lhs, const Vehicle &rhs) { return lhs.gear < rhs.gear; }
bool operator>(const Vehicle &lhs, const Vehicle &rhs) { return rhs < lhs; }

bool operator<=(const Vehicle &lhs, const Vehicle &rhs) { return !(lhs > rhs); }
bool operator>=(const Vehicle &lhs, const Vehicle &rhs) { return !(lhs < rhs); }

Vehicle& Vehicle::operator=(const Vehicle &rhs)
{
    ignition = rhs.ignition;
    gear = rhs.gear;
    colour = rhs.colour;
    std::cout << "(copy-assignment called)" << std::endl;
    return *this;
}

Vehicle& Vehicle::operator=(Vehicle &&rhs) noexcept
{
    if (this != &rhs){
        ignition = std::move(rhs.ignition);
        gear = std::move(rhs.gear);
        colour = std::move(rhs.colour);
        
        rhs.ignition = false;
        rhs.gear = 0;
        rhs.colour = "";
        
        std::cout << "(move-assignment called)" << std::endl;
    }
    return *this;
}

int main()
{
    std::cout << "Creating a car...\n";
    Vehicle m3_1 = { true, 1, "black" };
    std::cout << "m3_1: " << m3_1 << std::endl;
    
    std::cout << "\nCopying m3_1 to m3_2...\n";
    Vehicle m3_2;
    m3_2 = m3_1;
    std::cout << "m3_1: " << m3_1 << std::endl;
    std::cout << "m3_2: " << m3_2 << std::endl;
    
    std::cout << "\nMoving m3_1 into m3_3...\n";
    Vehicle m3_3;
    m3_3 = std::move(m3_1);
    std::cout << "m3_1: " << m3_1 << std::endl;
    std::cout << "m3_2: " << m3_2 << std::endl;
    std::cout << "m3_3: " << m3_3 << "(left in a state to be destroyed)" << std::endl;
    
    return 0;
}
