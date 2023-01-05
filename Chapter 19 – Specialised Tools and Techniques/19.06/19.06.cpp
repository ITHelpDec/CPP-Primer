// Exercise 19.06:
/*
 Write an expression to dynamically cast a pointer to a Query_base to a pointer to an AndQuery (§ 15.9.1, p. 636).
 Test the cast by using objects of AndQuery and of another query type.
 Print a statement indicating whether the cast works and be sure that the output matches your expectations.
*/

#include "TextQuery.hpp"
#include "Query_base.hpp"

int main()
{
    // "pointer to a Query_base" (Query_base is an abstract class??)
    Query_base *qb = nullptr;
    
    if (AndQuery *aq = dynamic_cast<AndQuery*>(qb)) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cerr << "No dice..." << std::endl;
    } // returns no cast (to be expected – nullptr)
    
    Query test1 = Query("woof") & Query("woof");
    Query test2= Query("you") | Query("me");
    
    // "Query" is not polymorphic
    // Query *tp = &test1;
    
    // Cannot initialize a variable of type 'Query_base *' with an rvalue of type 'Query *'
    // qb = test1;
    
    // if (AndQuery *aq = dynamic_cast<AndQuery*>(tp)) {
    //     std::cout << "Success!" << std::endl;
    // } else {
    //     std::cerr << "No dice..." << std::endl;
    // } // Cannot use dynamic_cast to convert from 'Query' to 'AndQuery *'
    
    // same for test2
    
    // I must be missing something because these questions are terrible
    
    return 0;
}
