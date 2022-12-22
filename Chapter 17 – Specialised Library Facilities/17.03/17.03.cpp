// Exercise 17.03:
/*
 Rewrite the TextQuery programs from § 12.3 (p. 484) to use a tuple instead of the QueryResult class.
 Explain which design you think is better and why.
 
 >> Whilst std::tuple<Args...> has reduced the lines of code with minimal refactoring, it has also reduced the intelligibility of our print function (it would be interesting to see if or how overall performance of the programme has been affected).
 
*/

#include "TextQuery.hpp"

int main()
{
    std::ifstream file("/<PATH>/storyDataFile");
    
    if (!file.is_open()) {
        std::cerr << "could not open file" << std::endl;
        return -1;
    }
    
    runQueries(file);
    
    file.close();
    
    return 0;
}

