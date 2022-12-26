// Exercise 17.31:
/*
 What would happen if we defined b and e inside the do loop of the game-playing program from this section?
 
 >> "Because enginers return the same sequence of numbers, it is essential that we declare engines out of loops. Otherwise, we'd create a new engine on each iteration and generate the same values on each iteration. Similarly, distributions may retain state and should also be defined outside loops" – pg. 752
 
 >> Game attached below with static engine and bernoulli distribution
*/

#include <string>
#include <random>
#include <iostream>

bool play(const bool &first) {
    static std::default_random_engine e;
    static std::bernoulli_distribution b;
    return b(e);
}

int main()
{
    std::string resp;
    std::default_random_engine e;
    std::bernoulli_distribution b;
    
    do {
        bool first = b(e);
        std::cout << (first ? "We go first." : "You get to go first.") << std::endl;
        
        std::cout << (play(first) ? "Sorry, you lost!" : "Congrats, you won!") << std::endl;
        
        std::cout << "Play again? Enter 'yes' or 'no': ";
    } while (std::cin >> resp && resp[0] == 'y');
    
    return 0;
}
