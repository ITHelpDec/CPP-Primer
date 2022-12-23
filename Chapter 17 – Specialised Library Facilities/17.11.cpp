// Exercise 17.11:
/*
 Define a data structure that contains an integral object to track responses to a true/false quiz containing 10 questions.
 What changes, if any, would you need to make in your data structure if the quiz had 100 questions?
 
 >> You could use a bitset within a struct and create some function to set and return answers
 >> You would need some way to keep track of candidates as well (some kind of container).
 
 >> You could also use a std::vector<booL> if you want more flexibility in terms of size(), ...
 >> ...as std::bitset<N> requires a constexpr N (could potentially specialise namespace std if we wanted)
 
*/

#include <bitset>
#include <iostream>

template <std::size_t N> struct Quiz {
    std::bitset<N> quiz;
    
    // we could also do the following:
    // std::bitset<10> quiz;
    // std::bitset<100> quiz;
    
    void markAsTrue_Question(int n)  { quiz.set(n - 1); }
    void markAsFalse_Question(int n) { quiz.reset(n - 1); }
    
    int answerToQuestion(int n)      { return quiz[n - 1]; }
};

int main()
{
    constexpr std::size_t sz = 10;
    Quiz<sz> candidate1;
    
    candidate1.markAsTrue_Question(10);
    std::cout << "Setting question 10 to \"True\"...\n";
    std::cout << "Candidate 1's answers: " << candidate1.quiz << "\n" << std::endl;
    
    std::cout << "Candidate 1's answer to question 10: "
              << (candidate1.answerToQuestion(10) ? "True" : "False") << "\n" << std::endl;
    
    candidate1.markAsFalse_Question(10);
    std::cout << "Setting question 10 to \"False\"...\n";
    std::cout << "Candidate 1's answers: " << candidate1.quiz << "\n" << std::endl;
    
    // another way to view answers using for loop
    std::cout << "Candidate 1's answers: " << std::endl;
    for (int i = 0; i != candidate1.quiz.size(); ++i) {
        std::cout << i + 1 << ": " << (candidate1.quiz[i] ? "True" : "False") << std::endl;;
    } std::cout << std::endl;
}
