// Exercise 19.07:
/*
 Write the same cast, but cast a Query_base object to a reference to AndQuery.
 Repeat the test to ensure that your cast works correctly.
 
 >> "abstract base class: Class that has one or more pure virtual functions."
 >> "We cannot create objects of an abstract base-class type." – pg. 649
 
 >> I'm not sure why these last two questions have been asked when it's not...
 >> ...possible to directly initialise a Query_base object
 
*/

#include "TextQuery.hpp"
#include "Query_base.hpp"

#include <typeinfo>

void f(const Query_base &qb) {
    try {
        const AndQuery &aq = dynamic_cast<const AndQuery&>(qb);
        
        if (typeid(aq) == typeid(Query_base))
            std::cout << "cast was a success" << std::endl;
        else
            std::cout << "cast didnae work" << std::endl;
    } catch (std::bad_cast &e) {
        std::cout << e.what() << ": oops!" << std::endl;
    }
}
