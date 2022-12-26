// Exercise 17.29:
/*
 Allow the user to supply a seed as an optional argument to the function you wrote in the previous exercise.
*/

#include <random>
#include <iostream>

int goodRand(const unsigned &seed) {
    static std::default_random_engine e(seed);
    static std::uniform_int_distribution u(0, 100);
    
    return u(e);
}

int main()
{
    std::cout << "This is a random number generator." << std::endl;
    std::cout << "Please enter a number from 0 to " << UINT_MAX << " to act as a seed for our generator...\n>>> ";
    
    unsigned seed;
    std::cin >> seed;
    
    std::cout << "Now keep pressing enter to generate a random number between 1-100:\n";
    
    while (std::cin.get()) {
        std::cout << ">>> " << goodRand(seed);
    } std::cout << std::endl;
    
    return 0;
}
