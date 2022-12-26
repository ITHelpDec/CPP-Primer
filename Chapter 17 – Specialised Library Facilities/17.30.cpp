// Exercise 17.30:
/*
 Revise your function again this time to take a minimum and maximum value for the numbers that the function should return.
*/

#include <random>
#include <iostream>

int goodRand(const unsigned &seed, const unsigned &min, const unsigned &max) {
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution u(min, max);
    
    return u(e);
}

int main()
{
    std::cout << "This is a random number generator." << std::endl;
    
    unsigned seed, min, max;
    
    std::cout << "Please enter a number from 0 to " << UINT_MAX << " to act as a seed for our generator...\n>>> ";
    std::cin >> seed;
    
    std::cout << "Now insert a minimum value...\n>>> ";
    std::cin >> min;
    
    std::cout << "...followed by a maximum value...\n>>> ";
    std::cin >> max;
    
    std::cout << "That's it!\nNow keep pressing enter to generate a random number between 1-100:\n";
    
    while (std::cin.get()) {
        std::cout << ">>> " << goodRand(seed, min, max);
    } std::cout << std::endl;
    
    return 0;
}
