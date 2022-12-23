// Exercise 17.13:
/*
 Write an integral object that contains the correct answers for the true/false quiz.
 Use it to generate grades on the quiz for the data structure from the previous two exercises.
*/

#include <bitset>
#include <iostream>

template <std::size_t N> class Quiz {
public:
    // create random answers
    Quiz() { setAnswers(); }
    
    void markAsTrue_Question(int n)  { quiz.set(n - 1); }
    void markAsFalse_Question(int n) { quiz.reset(n - 1); }
    
    int answerToQuestion(int n)      { return quiz[n - 1]; }
    
    // function declarations to create answers
    void setAnswers();

    // grade declaration
    double getGrade();
    
private:
    std::bitset<N> quiz;
    std::bitset<N> answers;
};

// function defintion for creating answers
template <std::size_t N> void Quiz<N>::setAnswers()
{
    // rand() is not very "rand"; would like to try std::mt19937
    for (int i = 0; i != N; ++i) { answers[rand() % N] = rand() % 2; }
}

// function to spit out score wth commented debug lines
template <std::size_t N> double Quiz<N>::getGrade()
{
    // std::cout << "\nQuiz   : " << quiz << std::endl;
    // std::cout << "Answers: " << answers << std::endl;
    return std::bitset<N>(quiz ^ answers).count() * 1.0 / N * 100;
}

int main()
{
    Quiz<10> candidate1;
    std::cout << "Creating Candidate 1...\n\n";
    
    candidate1.markAsTrue_Question(10);
    std::cout << "Setting question 10 to \"True\"...\n";
    
    std::cout << "Candidate 1's answer to question 10: "
              << (candidate1.answerToQuestion(10) ? "True" : "False") << std::endl;
    
    candidate1.markAsFalse_Question(10);
    std::cout << "Setting question 10 back to \"False\"...\n\n";
    
    Quiz<100> candidate2;
    std::cout << "Creating Candidate 2...\n\n";
    
    std::cout << "Candidate 1 got " << candidate1.getGrade() << "%" << std::endl;
    std::cout << "Candidate 2 got " << candidate2.getGrade() << "%\n" << std::endl;
    
    return 0;
}
