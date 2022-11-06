
#ifndef Query_base_hpp
#define Query_base_hpp

#include "TextQuery.hpp"
#include "QueryResult.hpp"

#include <string>

// abstract class acts as a base class for concrete query types; all members are private
class Query_base {
    // members of Query have been granted permission to access the virtual functions of this abstract base class
    friend class Query;
protected:
    // used in the eval functions
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    // eval returns the QueryResult that matches this Query (pure virtual)
    virtual QueryResult eval(const TextQuery&) const = 0;
    // rep is a string representation of the Query
    virtual std::string rep() const = 0;
};

#endif /* Query_base_hpp */
