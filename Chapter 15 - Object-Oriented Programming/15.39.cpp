// Exercise 15.39:
/*
 Implement the Query and Query_base classes.
 Test your application by evaluating and printing a query such as the one in Figure 15.3 (p. 638).
 
 >> got fed up of the "1 duplicate symbol for architecture x86_64" error being spat out by Xcode so included everything as one file and inlined all functions outside hte class to get it to run...
*/

#include <iostream>
#include <string>
#include <memory>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    using line_no = std::size_t;
    
    // default constructor eval() functions to compile properly
    QueryResult() = default;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
    
    std::set<line_no>::iterator begin() { return lines->begin(); }
    std::set<line_no>::iterator end() { return lines->end(); }
    
    std::set<line_no>::const_iterator cbegin() const { return lines->cbegin(); }
    std::set<line_no>::const_iterator cend() const { return lines->cend(); }
    
    std::shared_ptr<std::vector<std::string>> get_file() { return file; }
    
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

class TextQuery {
public:
    using line_no = std::size_t;
    
    // using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    // input file
    std::shared_ptr<std::vector<std::string>> file;
    // map of each word to the set of the lines in which that word appears
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

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
    QueryResult eval(const TextQuery&) const;
    
    std::string rep() const;
private:
    Query(std::shared_ptr<Query_base> query) : q(query) { }
    std::shared_ptr<Query_base> q;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query)
{
    // Query::rep makes a virtual call through its Query_base pointer to rep()
    return os << query.rep();
}

class WordQuery : public Query_base {
// "private:" implictly declared
    // Query uses the WordQuery constructor
    friend class Query;
    WordQuery(const std::string &s) : query_word(s)
    { /* std::cout << "WordQuery(const std::string&)" << std::endl; */ }
    
    // concrete class: WordQuery defines all inherited pure virtual functions
    QueryResult eval(const TextQuery &t) const override
    {
        // std::cout << "QueryResult::eval()" << std::endl;
        return t.query(query_word);
    }
    
    std::string rep() const override
    {
        // std::cout << "QueryResult::rep()" << std::endl;
        return query_word;
    }
    
    // word for which to search
    std::string query_word;
};

class NotQuery : public Query_base {
    friend Query operator~(const Query&);
    NotQuery(const Query &q) : query(q) { }
    
    // concrete class: NotQuery defines all inherited pure virtual functions
    std::string rep() const override { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const override;
    Query query;
};

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) { }
    
    // abstract class: BinaryQuery doesn't define eval
    
    std::string rep() const override { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
    
    // right- and left-hand operands
    Query lhs, rhs;
    
    // name of the operator
    std::string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") { }
    
    // concrete class: AndQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { }
    
    // concrete class: OrQuery inherits rep and defines the remaining pure virtual
    QueryResult eval(const TextQuery&) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

// simple, but proud of this one :)
inline std::string make_plural(const std::size_t &sz, const std::string &word, const std::string &s)
{
    std::string result;
    return sz == 1 ? word : word + s;
}

inline std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    // if the word was found, print the count and all occurences
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    
    // print each line in which the word appeared
    // for every element in the set
    for (const auto &num : *qr.lines)
        // don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}

// read the input file and build the map of lines to line numbers
inline TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    // for each line in the file
    while (std::getline(is, text)) {
        // remember this line of text
        file->push_back(text);
        // make a note of the current line number
        std::size_t n = file->size() - 1;
        // separate the line into words
        std::stringstream line(text);
        std::string word;
        // for each word in that line
        while (line >> word) {
            // if word isn't already in wm, subscripting adds a new entry
            // lines is a shared_ptr
            auto &lines = wm[word];
            
            // that pointer is null the first time we see word
            if (!lines)
                // allocate a new set
                lines.reset(new std::set<line_no>);
            // thereafter, insert this line number
            lines->insert(n);
        }
    }
}

inline QueryResult TextQuery::query(const std::string &sought) const
{
    // we'll return a pointer to this set if we don't find sought
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    
    // if not found...otherwise..
    return loc == wm.end() ? QueryResult(sought, nodata, file) : QueryResult(sought, loc->second, file);
}

inline QueryResult NotQuery::eval(const TextQuery &text) const
{
    // std::cout << "NotQuery::eval() called" << std::endl;
    
    // virtual call to eval through the Query operand
    auto result = query.eval(text);
    
    // start out with an empty result set
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    // we have to iterate through the lines on which our operand appears
    auto beg = result.begin(), end = result.end();
    
    // for each line in the input file, if that line if not in result,
    // add that line number to ret_lines
    auto sz = result.get_file()->size();
    
    for (std::size_t n = 0; n != sz; ++n) {
        // if we haven't processed all the lines in result, ...
        // ...check whether this line is present
        if (beg == end || *beg != n)
            // unsuccessful
            ret_lines->insert(n);
        else if (beg != end)
            // successful
            ++beg;
        
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}

inline QueryResult AndQuery::eval(const TextQuery &text) const {
    // std::cout << "AndQuery::eval(const TextQuery &t) const" << std::endl;
    
    // virtual calls through the Query operands to get the result sets for the operands
    auto left = lhs.eval(text), right = rhs.eval(text);
    
    // set to hold the intersection of left and right
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    // writes the intersection of two ragnes to a destination iterator
    // destination iterator in this call adds elements to set
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
    
    return QueryResult(rep(), ret_lines, left.get_file());
}

inline QueryResult OrQuery::eval(const TextQuery &text) const
{
    // std::cout << "OrQuery::eval" << std::endl;
    
    // virtual calls through the Query members – lhs and rhs
    // the calls to eval return the QueryResult for each operand
    auto right = rhs.eval(text), left = lhs.eval(text);
    
    // copy the line number from the left-hand operand into the result set
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    
    // insert lines from the right-hand operand
    ret_lines->insert(right.begin(), left.begin());
    
    // return the new QueryResult representing the union of lhs and rhs
    return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query::Query(const std::string &s) : q(new WordQuery(s))
{
    // std::cout << "Query::Query(const std::string&)" << std::endl;
}

inline QueryResult Query::eval(const TextQuery &t) const
{
    // std::cout << "Query::eval(const TextQuery&) const" << std::endl;
    return q->eval(t);
}

inline std::string Query::rep() const
{
    // std::cout << "Query::rep() const" << std::endl;
    return q->rep();
}

// infile is an ifstream that is the file we want to query
inline void runQueries(std::ifstream &infile)
{
    // store the file and build the query
    TextQuery tq(infile);
    
    // iterate with the user: promppt for a word to find and print results
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        
        // stop if we hit end-of-file on hte input or if a 'q' is entered
        if (!(std::cin >> s) || s == "q") break;
        // run the query and print the results
        print(std::cout, tq.query(s)) << std::endl;
    }
}

int main()
{

    Query q = Query("fiery") & Query("bird") | Query("wind");

    std::cout << q << std::endl;

    return 0;
}
