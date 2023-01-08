// Exercise 19.20:
/*
 Nest your QueryResult class inside TextQuery and rerun the pro- grams you wrote to use TextQuery in § 12.3.2 (p. 490).
*/

#include "TextQuery.hpp"
#include "Query_base.hpp"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        
        if (!(std::cin >> s) || s == "q") break;
        
        print(std::cout, tq.query(s)) << std::endl;
    }
}

int main()
{
    std::ifstream file("storyDataFile");
    
    runQueries(file);
    
    return 0;
}
