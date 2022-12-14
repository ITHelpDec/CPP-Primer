// Exercise 13.41:
/*
 Why did we use postfix increment in the call to construct inside push_back?
 What would happen if it used the prefix increment?
 
 >> Changes highlighted in comments.
*/

#include <fstream>
#include <iostream>
#include <string>
// #include <vector>
#include "StrVec.h"
#include <map>
#include <set>
#include <memory>
#include <sstream>


class QueryResult;

class TextQuery {
public:
    // using line_no = std::vector<std::string>::size_type;
    using line_no = std::size_t;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    // std::shared_ptr<std::vector<std::string>> file;
    std::shared_ptr<StrVec> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    using line_no = std::size_t;
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    // QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<StrVec> f) : sought(s), lines(p), file(f) { }
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    // std::shared_ptr<std::vector<std::string>> file;
    std::shared_ptr<StrVec> file;
};

// TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
TextQuery::TextQuery(std::ifstream &is) : file(new StrVec)
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

QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

std::string make_plural(const std::size_t &sz, const std::string &word, const std::string &s)
{
    std::string result;
    if (sz == 1 )
        return word;
    return word + s;
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    
    for (auto num : *qr.lines)
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}

int main()
{
    std::ifstream file("/13.42_in.txt");
    
    runQueries(file);
    
    return 0;
}
