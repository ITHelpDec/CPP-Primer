// Exercise 19.07:
/*
 Write the same cast, but cast a Query_base object to a reference to AndQuery.
 Repeat the test to ensure that your cast works correctly.
 
 >> "abstract base class: Class that has one or more pure virtual functions."
 >> "We cannot create objects of an abstract base-class type." – pg. 649
 
 >> I'm not sure why these last two questions have been asked when it's not...
 >> ...possible to directly initialise a Query_base object
 
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

class QueryResult;

class TextQuery {
public:
    using line_no = std::size_t;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    using line_no = std::size_t;
    
    // default constructor eval() functions to compile properly
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

inline QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    
    auto loc = wm.find(sought);
    
    return loc == wm.end() ? QueryResult(sought, nodata, file) : QueryResult(sought, loc->second, file);
}
