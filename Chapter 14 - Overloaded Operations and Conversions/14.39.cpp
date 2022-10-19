// Exercise 14.39:
/*
 Revise the previous program to report the count of words that are sizes 1 through 9 and 10 or more.
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class MatchBound {
public:
    MatchBound() : lower_bound(1), upper_bound(10) { }
    MatchBound(std::string::size_type lb, std::string::size_type ub) : lower_bound(lb), upper_bound(ub) { }
    
    bool operator() (const std::string &s) { return (s.size() >= lower_bound && s.size() <= upper_bound); }
    
private:
    std::string::size_type lower_bound;
    std::string::size_type upper_bound;
};

int main(int argc, const char *argv[])
{
    if (argc < 2) { std::cerr << "Input file missing – please try again." << std::endl; return -1; }
    if (argc > 2) { std::cerr << "Too many input files – please try again." << std::endl; return -1; }
    
    std::ifstream in(argv[1]);
    if (!(in.is_open())) { std::cerr << "File could not be opened – please try again." << std::endl; return -1; }
    
    std::vector<std::string> svec;
    std::string word;
    
    while (in >> word) { svec.push_back(word); }
    
    in.close();
    
    if (svec.empty()) { std::cerr << "File was empty – please provide valid input." << std::endl; return -1; }
    
    // custom MatchBound(lb, ub) predicate
    std::vector<std::string>::size_type lb = 1, ub = 9;
    std::cout << "How many words are between " << lb << " and " << ub << " characters long?: ";
    auto one_to_nine = std::count_if(svec.begin(), svec.end(), MatchBound(lb, ub));
    std::cout << one_to_nine << std::endl;
    
    // 10 or more? just take last sum away from size()
    std::cout << "How many words have more than " << ub + 1 << " characters?: ";
    std::cout << svec.size() - one_to_nine << std::endl;
    
    return 0;
}
