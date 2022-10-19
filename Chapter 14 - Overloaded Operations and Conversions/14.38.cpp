// Exercise 14.38:
/*
 Write a class that tests whether the length of a given string matches a given bound.
 Use that object to write a program to report how many words in an input file are of sizes 1 through 10 inclusive.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class MatchBound {
public:
    // default / adjustable constructors
    MatchBound() : lower_bound(1), upper_bound(10) { }
    MatchBound(std::string::size_type lb, std::string::size_type ub) : lower_bound(lb), upper_bound(ub) { }
    
    // return true if 1 <= x <= 10
    bool operator() (const std::string &s) { return (s.size() >= lower_bound && s.size() <= upper_bound); }
    
private:
    std::string::size_type lower_bound;
    std::string::size_type upper_bound;
};

int main(int argc, const char *argv[])
{
    // check for input file
    if (argc < 2) { std::cerr << "Input file missing – please try again." << std::endl; return -1; }
    if (argc > 2) { std::cerr << "Too many input files – please try again." << std::endl; return -1; }
    
    // check opened correctly
    std::ifstream in(argv[1]);
    if (!(in.is_open())) { std::cerr << "File could not be opened – please try again." << std::endl; return -1; }
    
    // create containers
    std::vector<std::string> svec;
    std::string word;
    
    // for as long as there is valid input, add each word from input file to vector
    while (in >> word) { svec.push_back(word); }
    
    in.close();
    
    // check vector isn't empty before running algorithms
    if (svec.empty()) { std::cerr << "File was empty – please provide valid input." << std::endl; return -1; }
    
    // MatchBound() predicate
    std::cout << "How many words are at least 1 to 10 characters long?: ";
    std::cout << (std::count_if(svec.begin(), svec.end(), MatchBound())) << std::endl;
    
    // custom MatchBound(lb, ub) predicate
    std::vector<std::string>::size_type lb = 1, ub = 1;
    std::cout << "How many words are between " << lb << " and " << ub << " characters long?: ";
    std::cout << (std::count_if(svec.begin(), svec.end(), MatchBound(lb, ub))) << std::endl;
    
    return 0;
}
