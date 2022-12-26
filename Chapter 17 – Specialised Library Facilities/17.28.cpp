// Exercise 17.28:
/*
 Write a function that generates and returns a uniformly distributed random unsigned int each time it is called.
*/

#include <random>
#include <iostream>

int goodRand() {
    static std::default_random_engine e;
    static std::uniform_int_distribution u(0, 9);
    
    return u(e);
}

int main()
{
    std::cout << "This is a random number generator." << std::endl;
    std::cout << "Keep pressing enter to generate a random number between 1-100:\n>>> ";
    
    while (std::cin.get()) {
        std::cout << ">>> " << goodRand();
    } std::cout << std::endl;
    
    return 0;
}
