
#ifndef Query_hpp
#define Query_hpp

#include "Query_base.hpp"
#include "QueryResult.hpp"
#include "TextQuery.hpp"
#include "WordQuery.hpp"

#include <string>

#include <utility>
#include <iostream>

// interface class to manage the QUery_base inheritance hierarchy
class Query {
    // these operators need access to the shared_ptr constructor
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    // builds a new WordQuery
    Query(const std::string&);
    
    // interface functions call the corresponding Query_base operations
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query) : q(query) { }
    std::shared_ptr<Query_base> q;
};

// allocates a WordQuery and initialises its pointer member to that newly-allocated object
inline Query::Query(const std::string &s) : q(new WordQuery(s)) { }

std::ostream &operator<<(std::ostream &os, const Query &query)
{
    // Query::rep makes a virtual call through its Query_base pointer to rep()
    return os << query.rep();
}

#endif /* Query_hpp */
