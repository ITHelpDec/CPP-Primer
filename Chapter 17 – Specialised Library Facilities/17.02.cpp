// Exercise 17.02:
/*
 Define a tuple that holds a string, a vector<string>, and a pair<string, int>.
*/

#include <string>
#include <vector>
#include <utility>
#include <iostream>

void printVec(const std::vector<std::string> &svec) {
    for (const auto &s : svec) { std::cout << s << " "; }
}

int main()
{
    std::string s = "half man";
    std::vector<std::string> svec = { "half", "bear" };
    std::pair<std::string, int> p = { "half pig" , 1337 };
    
    std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> exercise(s, svec, p);
    
    std::cout << "exercise: ";
    std::cout << std::get<0>(exercise) << " , ";
    printVec(std::get<1>(exercise));
    std::cout << ", " << std::get<2>(exercise).first << std::endl;
    
    return 0;
}
