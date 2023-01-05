// Exercise 19.08:
/*
 Write a typeid expression to see whether two Query_base pointers point to the same type.
 Now check whether that type is an AndQuery.
 
 >> A bit messy, but have included growing memory deletions within catch statements...
 >> ..., on the off-chance that an exception is thrown and the stack is unwound
 
*/

#include "TextQuery.hpp"
#include "Query_base.hpp"

#include <typeinfo>

int main()
{
    Query_base *qbp1 = nullptr, *qbp2 = nullptr;
    
    try {
        if (typeid(*qbp1) == typeid(*qbp2))
            std::cout << "both Query_base pointers point to the same type" << std::endl;
        else
            std::cout << "nope – not the smae" << std::endl;
    } catch (std::bad_typeid &e) {
        // If p is a null pointer, then typeid(*p) throws a bad_typeid exception – pg. 828
        std::cerr << e.what() << ": looks like a std::bad_typeid to me (nullptr)" << std::endl;
    }
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    Query *qp = new Query("woof");
    
    try {
        if (typeid(*qp) == typeid(AndQuery))
            std::cout << "yup! it's an AndQuery" << std::endl;
        else
            std::cout << "sorry – not an AndQuery! it's a " << typeid(*qp).name() << std::endl;
    } catch (std::bad_typeid &e) {
        std::cerr << e.what() << ": looks like a std::bad_typeid to me" << std::endl;
        delete qp;
    }
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    Query *aq = new Query(Query("woof") & Query("woof"));
    
    try {
        if (typeid(*aq) == typeid(AndQuery))
            std::cout << "yup! it's an AndQuery" << std::endl;
        else
            std::cout << "sorry – not an AndQuery! it's a " << typeid(*aq).name() << std::endl;
    } catch (std::bad_typeid &e) {
        std::cerr << e.what() << ": looks like a std::bad_typeid to me" << std::endl;
        delete qp;
        delete aq;
    }
    
    delete qp;
    delete aq;
    
    return 0;
}
