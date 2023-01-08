// Exercise 19.20:
/*
 Nest your QueryResult class inside TextQuery and rerun the pro- grams you wrote to use TextQuery in § 12.3.2 (p. 490).
*/

class Query_base {
    friend class Query;
protected:
    using line_no = TextQuery::line_no;
    virtual ~Query_base() = default;
private:
    // virtual QueryResult eval(const TextQuery&) const = 0;
    virtual TextQuery::QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~(const Query&);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    
    // QueryResult eval(const TextQuery&) const;
    TextQuery::QueryResult eval(const TextQuery&) const;
    
    std::string rep() const;
private:
    Query(std::shared_ptr<Query_base>);
    std::shared_ptr<Query_base> q;
};

class WordQuery : virtual public Query_base {
    friend class Query;
    
    WordQuery(const std::string&);
    
    // QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&) const override;
    
    std::string rep() const override;
    
    std::string query_word;
};

class NotQuery : virtual public Query_base {
    friend Query operator~(const Query&);
    
    NotQuery(const Query&);
    
    std::string rep() const override;
    
    // QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&) const override;
    
    Query query;
};

class BinaryQuery : virtual public Query_base {
protected:
    BinaryQuery(const Query &l, const Query &r, std::string s)
        : lhs(l), rhs(r), opSym(s) { }
    
    std::string rep() const override;
    
    Query lhs, rhs;
    
    std::string opSym;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query&, const Query&);
    
    AndQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "&") { }
    
    // QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&) const override;
};

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query&, const Query&);
    
    OrQuery(const Query &left, const Query &right)
        : BinaryQuery(left, right, "|") { }
    
    // QueryResult eval(const TextQuery&) const override;
    TextQuery::QueryResult eval(const TextQuery&) const override;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

inline Query operator|(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

inline Query operator&(const Query &lhs, const Query &rhs)
{
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

inline Query::Query(const std::string &s) : q(new WordQuery(s)) { }

// inline QueryResult Query::eval(const TextQuery &t) const
inline TextQuery::QueryResult Query::eval(const TextQuery &t) const
{
    return q->eval(t);
}

inline std::string Query::rep() const
{
    return q->rep();
}

inline Query::Query(std::shared_ptr<Query_base> query) : q(query) { }

inline WordQuery::WordQuery(const std::string &s) : query_word(s) { }

// inline QueryResult WordQuery::eval(const TextQuery &t) const
inline TextQuery::QueryResult WordQuery::eval(const TextQuery &t) const
{
    return t.query(query_word);
}

inline std::string WordQuery::rep() const
{
    return query_word;
}

inline NotQuery::NotQuery(const Query &q) : query(q) { }

inline std::string NotQuery::rep() const
{
    return "~(" + query.rep() + ")";
}

inline std::string BinaryQuery::rep() const
{
    return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")";
}

// inline QueryResult AndQuery::eval(const TextQuery &text) const {
inline TextQuery::QueryResult AndQuery::eval(const TextQuery &text) const {
    auto left = lhs.eval(text), right = rhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
    
    // return QueryResult(rep(), ret_lines, left.get_file());
    return TextQuery::QueryResult(rep(), ret_lines, left.get_file());
}

// inline QueryResult OrQuery::eval(const TextQuery &text) const
inline TextQuery::QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto right = rhs.eval(text), left = lhs.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
    ret_lines->insert(right.begin(), left.begin());
    
    // return QueryResult(rep(), ret_lines, left.get_file());
    return TextQuery::QueryResult(rep(), ret_lines, left.get_file());
}

// inline QueryResult NotQuery::eval(const TextQuery &text) const
inline TextQuery::QueryResult NotQuery::eval(const TextQuery &text) const
{
    auto result = query.eval(text);
    auto ret_lines = std::make_shared<std::set<line_no>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    
    for (std::size_t n = 0; n != sz; ++n) {
        if (beg == end || *beg != n) {
            ret_lines->insert(n);
        } else if (beg != end) {
            ++beg;
        }
    }

    // return QueryResult(rep(), ret_lines, result.get_file());
    return TextQuery::QueryResult(rep(), ret_lines, result.get_file());
}

// simple, but proud of this one :)
inline std::string make_plural(const std::size_t &sz, const std::string &word, const std::string &s)
{
    std::string result;
    return sz == 1 ? word : word + s;
}

// inline std::ostream &print(std::ostream &os, const QueryResult &qr)
inline std::ostream &print(std::ostream &os, const TextQuery::QueryResult &qr)
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

inline std::ostream &operator<<(std::ostream &os, const Query &query)
{
    return os << query.rep();
}
