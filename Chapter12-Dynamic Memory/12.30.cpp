// Exercise 12.30:
/*
 Define your own versions of the TextQuery and QueryResult classes and execute the runQueries function from § 12.3.1 (p. 486).
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <sstream>

class QueryResult;

class TextQuery {
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    // input file
    std::shared_ptr<std::vector<std::string>> file;
    // map of each word to the set of the lines in which that word appears
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    // also need "using" / "typedef" in this class unless we want to announce it globally
    // otherwise functions will not work
    using line_no = std::vector<std::string>::size_type;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(std::ifstream &is) : file(new std::vector<std::string>)
{
    std::string text;
    // for each line in the file
    while (std::getline(is, text)) {
        // remember this line of text
        file->push_back(text);
        // make a note of the current line number
        int n = file->size() - 1;
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

QueryResult TextQuery::query(const std::string &sought) const
{
    // we'll return a pointer to this set if we don't find sought
    static std::shared_ptr<std::set<line_no>> nodata(new std::set<line_no>);
    
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        // not found
        return QueryResult(sought, nodata, file);
    else
        return QueryResult(sought, loc->second, file);
}

// infile is an ifstream that is the file we want to query
void runQueries(std::ifstream &infile)
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

// simple, but proud of this one :)
std::string make_plural(const std::vector<std::string>::size_type &sz, const std::string &word, const std::string &s)
{
    std::string result;
    if (sz == 1)
        return word;
    return word + s;
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    // if the word was found, print the count and all occurences
    os << qr.sought << " occurs " << qr.lines->size() << " " << make_plural(qr.lines->size(), "time", "s") << std::endl;
    
    // print each line in which the word appeared
    // for every element in the set
    for (auto num : *qr.lines)
        // don't confound the user with text lines starting at 0
        os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
    return os;
}

int main()
{
    std::ifstream file("./12.30_in.txt");
    
    runQueries(file);
    
    return 0;
}
