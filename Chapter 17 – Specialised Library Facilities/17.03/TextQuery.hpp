// Exercise 17.03:
/*
 Rewrite the TextQuery programs from § 12.3 (p. 484) to use a tuple instead of the QueryResult class.
 Explain which design you think is better and why.
 
 >> Whilst std::tuple<Args...> has reduced the lines of code with minimal refactoring, it has also reduced the intelligibility of our print function (it would be interesting to see if or how overall performance of the programme has been affected).
 
*/

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

// forward declaration and class body removed
// class QueryResult;

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    
    // new "using" line for the sake of brevity
    using QueryResult = std::tuple<std::string,
                                   std::shared_ptr<std::set<line_no>>,
                                   std::shared_ptr<std::vector<std::string>>>;
    
    TextQuery(std::ifstream&);
    
    // same as before – no change needed thanks to "using"
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    while (std::getline(is, text)) {
        file->push_back(text);
        int n = file->size() - 1;
        std::istringstream line(text);
        std::string word;
        while (line >> word) {
            auto &lines = wm[word];
            if (!lines) { lines.reset(new std::set<line_no>); }
            lines->insert(n);
        }
    }
}

// QueryResult TextQuery::query(const std::string &sought) const
TextQuery::QueryResult TextQuery::query(const std::string &sought) const
{
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    auto loc = wm.find(sought);
    return loc == wm.end()
        ? QueryResult(sought, nodata, file)
        : QueryResult(sought, loc->second, file);
}

// std::ostream& print(std::ostream &os, const QueryResult &qr)
std::ostream& print(std::ostream &os, const TextQuery::QueryResult &qr)
{
    // not the most intuitive (typedef and using did not work)
    // qr.sought => std::get<0>(qr)
    // qr.lines  => std::get<1>(qr)
    // qr.file   => std::get<2>(qr)
    
    os << std::get<0>(qr) << " occurs " << std::get<1>(qr)->size() << " " <<
        (std::get<1>(qr)->size() == 1 ? "time." : "times.") << std::endl;
    for (auto &num : *std::get<1>(qr))
        os << "\t(line " << num + 1 << ") "
           << *(std::get<2>(qr)->begin() + num) << std::endl;
    return os;
}

void runQueries(std::ifstream &infile) {
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") { break; }
        print(std::cout, tq.query(s)) << std::endl;
    }
}
