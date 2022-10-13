// Exercise 14.05:
/*
 In exercise 7.40 from § 7.5.1 (p. 291) you wrote a sketch of one of the following classes.
 Decide what, if any, overloaded operators your class should provide.
 
 >> Can't think of any overloaded operators that would provide useful in this scenario bar maybe friend << or >> operators for input and output of something like the colour of the car.
*/

#include <iostream>

class Vehicle {
public:
    Vehicle() = default;
    
    void turn_on() { ignition = true; }
    void turn_off() { ignition = false; }
    std::string state() { return (ignition ? "on" : "off"); }
    std::size_t current_gear() { return gear; }
    void shift_up();
    void shift_down();
    
private:
    bool ignition = 0;
    std::size_t gear = 1;
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

int main()
{
    Vehicle m3;
    
    std::cout << "Turning car on...";
    m3.turn_on();
    std::cout << "(car is now " << m3.state() << ")\n" << std::endl;
    
    m3.shift_up();
    m3.shift_up();
    m3.shift_up();
    m3.shift_up();
    m3.shift_up();
    m3.shift_up();
    
    std::cout << "\nCurrent gear is " << m3.current_gear() << ".\n" << std::endl;
    
    m3.shift_down();
    m3.shift_down();
    m3.shift_down();
    m3.shift_down();
    m3.shift_down();
    m3.shift_down();
    
    std::cout << "\nCurrent gear is " << m3.current_gear() << "." << std::endl;
    
    std::cout << "\nTurning car off...";
    m3.turn_off();
    std::cout << "(car is now " << m3.state() << ")" << std::endl;
    
    
    return 0;
}
