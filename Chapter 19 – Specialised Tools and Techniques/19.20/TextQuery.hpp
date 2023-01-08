// Exercise 19.20:
/*
 Nest your QueryResult class inside TextQuery and rerun the pro- grams you wrote to use TextQuery in § 12.3.2 (p. 490).
*/

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <algorithm>
#include <iterator>

// class QueryResult;

class TextQuery {
public:
    // declaration nested
    class QueryResult;
    
    using line_no = std::size_t;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

// class QueryResult {

// nested class defined
class TextQuery::QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    // "using" already included in TextQuery – no need to redefine
    // using line_no = std::size_t;
    
    // need to preface all QueryResults members within new nested TextQuery::QueryResult:: scope
    // QueryResult() = default;
    // QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f)
    //     : sought(s), lines(p), file(f) { }
    
    QueryResult() = default;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f)
    : sought(s), lines(p), file(f) { }

    
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

// inline QueryResult TextQuery::query(const std::string &sought) const

// again, change of scope needed
inline TextQuery::QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    
    auto loc = wm.find(sought);
    
    return loc == wm.end() ? QueryResult(sought, nodata, file) : QueryResult(sought, loc->second, file);
}
