// Exercise 14.19:
/*
 Should the class you chose for exercise 7.40 from § 7.5.1 (p. 291) define the relational operators?
 If so, implement them.
 If not, explain why not.
 
 >> Could probably functions to discern gear positions
*/

#include <iostream>
#include <string>

class Vehicle {
    // relational operators
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

// "<" operator
bool operator<(const Vehicle &lhs, const Vehicle &rhs)
{
    return lhs.gear < rhs.gear;
}

// ">" operator
bool operator>(const Vehicle &lhs, const Vehicle &rhs)
{
    return rhs < lhs;
}

// "<=" operator
bool operator<=(const Vehicle &lhs, const Vehicle &rhs)
{
    return !(lhs > rhs);
}


// ">=" operator
bool operator>=(const Vehicle &lhs, const Vehicle &rhs)
{
    return !(lhs < rhs);
}


int main()
{
    std::cout << "Creating four cars in various gears...\n";
    Vehicle m3_1 = { true, 1, "black" };
    Vehicle m3_2 = { true, 2, "black" };
    Vehicle m3_3 = { true, 2, "black" };
    Vehicle m3_4 = { true, 3, "black" };
    
    std::cout << "m3_1 < m3_2...\n";
    std::cout << (m3_1 < m3_2 ? "Same gear." : "Different gear.") << std::endl;
    
    std::cout << "\nm3_2 <= m3_3...\n";
    std::cout << (m3_2 <= m3_3 ? "Same gear." : "Different gear.") << std::endl;
    
    std::cout << "\nm3_3 >= m3_4...\n";
    std::cout << (m3_3 >= m3_4 ? "Same gear." : "Different gear.") << std::endl;
    
    std::cout << "\nm3_4 > m3_1...\n";
    std::cout << (m3_4 > m3_1 ? "Same gear." : "Different gear.") << std::endl;
    
    return 0;
}
