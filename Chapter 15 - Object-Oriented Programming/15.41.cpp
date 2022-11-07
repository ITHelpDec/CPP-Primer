// Exercise 15.41:
/*
 Reimplement your classes to use built-in pointers to Query_base rather than shared_ptrs.
 Remember that your classes will no longer be able to use the synthesized copy-control members.
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
    
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    
    // new copy control members
    Query(const Query&);
    Query& operator=(const Query&);
    
    //Query(Query &&);
    //Query &operator=(Query &&);
    
    ~Query();
    
    QueryResult eval(const TextQuery&) const;
    std::string rep() const;
private:
    // this one uses a pointer to a rvalue reference
    // we also create a reference counter to keep track of pointers for later deletion
    // Query(std::shared_ptr<Query_base> query) : q(query) { }
    Query(Query_base *&&query) : q(query), ref_count(new std::size_t(1))
    { query = nullptr; }
    
    // std::shared_ptr<Query_base> q;
    Query_base *q;
    std::size_t *ref_count;
};

inline std::ostream &operator<<(std::ostream &os, const Query &query)
{ return os << query.rep(); }

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s) : query_word(s)
    { /* std::cout << "WordQuery(const std::string&)" << std::endl; */ }
    
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
    
    std::string query_word;
};

class NotQuery : public Query_base {
    friend Query operator~(const Query&);
    NotQuery(const Query &q) : query(q) { }
    
    std::string rep() const override { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery&) const override;
    Query query;
};

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) { }
    
    std::string rep() const override { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
    
    Query lhs, rhs;
    
    std::string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") { }
    
    QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { }
    
    QueryResult eval(const TextQuery&) const override;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
    // using built-in pointers
    // return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    // return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
    return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query &operand)
{
    // return std::shared_ptr<Query_base>(new NotQuery(operand));
    return new NotQuery(operand);
}

inline std::string make_plural(const std::size_t &sz, const std::string &word, const std::string &s)
{
    std::string result;
    return sz == 1 ? word : word + s;
}

inline std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    
    for (const auto &num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    
    return os;
}

inline TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        std::size_t n = file->size() - 1;
        std::stringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines)
                lines.reset(new std::set<line_no>);
            lines->insert(n);
        }
    }
}

inline QueryResult TextQuery::query(const std::string &sought) const
{
    // static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    static std::set<line_no> nodata = new std::set<line_no>;
    
    auto loc = wm.find(sought);
    return loc == wm.end() ? QueryResult(sought, nodata, file) : QueryResult(sought, loc->second, file);
}

inline QueryResult NotQuery::eval(const TextQuery &text) const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    
    for (std::size_t n = 0; n != sz; ++n) {
        if (beg == end || *beg != n) { ret_lines->insert(n); }
        else if (beg != end) { }++beg; }
    }
    return QueryResult(rep(), ret_lines, result.get_file());
}

inline QueryResult AndQuery::eval(const TextQuery &text) const {
    // std::cout << "AndQuery::eval(const TextQuery &t) const" << std::endl;
    
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
    
    return QueryResult(rep(), ret_lines, left.get_file());
}

inline QueryResult OrQuery::eval(const TextQuery &text) const
{
    // std::cout << "OrQuery::eval" << std::endl;
    
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    
    ret_lines->insert(right.begin(), left.begin());
    
    return QueryResult(rep(), ret_lines, left.get_file());
}

inline Query::Query(const std::string &s) : q(new WordQuery(s))
{
    // std::cout << "Query::Query(const std::string&)" << std::endl;
}

// destroy dynamically-allocated memory properly
Query::~Query() {
    if (--*ref_count == 0) {
        delete q;
        delete ref_count;
    }
}

// copy constructor
Query::Query(const Query &rhs) : q(rhs.q), ref_count(rhs.ref_count) { ++*ref_count; }

// copy-assignment operator
Query &Query::operator=(const Query &rhs)
{
    if (this != &rhs) {
        if (--*ref_count == 0) {
            delete q;
            delete ref_count;
        }
        q = rhs.q;
        ref_count = rhs.ref_count;
        ++*ref_count;
    }
  return *this;
}

// Query::Query(Query &&rhs) : q(std::move(rhs.q)), ref_count(std::move(rhs.ref_count))
// {
//     delete rhs.q;
//     // delete rhs.ref_count;
//     rhs.q = rhs.ref_count = nullptr;
// }

// Query &Query::operator=(Query &&rhs)
// {
//     if (this != &rhs) {
//         if (--*ref_count == 0) {
//             delete q;
//             delete ref_count;
//         }
//         q = std::move(rhs.q);
//         ref_count = std::move(rhs.ref_count);
//         rhs.q = rhs.ref_count = nullptr;
//     }
//     return *this;
// }

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

inline void runQueries(std::ifstream &infile)
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

    Query q = Query("fiery") & Query("bird") | Query("wind");

    std::cout << q << std::endl;

    return 0;
}
