// Exercise 12.27:
/*
 The TextQuery and QueryResult classes use only capabilities that we have already covered.
 Without looking ahead, write your own versions of these classes.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

// gave it a go without looking ahead - not quite there yet
// have added notes to explain why the things exist for any others reading

// QueryResult declaration needed early on in order to prime TextQuery member further down
class QueryResult;

class TextQuery {
public:
    // "using" used to de-improve intelligibility of code in map
    using line_no = std::vector<std::string>::size_type;
    
    // define constructor to take input file
    TextQuery(std::ifstream&);
    
    // declare "query" member of type "QueryResult" that takes a string const and performs a function on a const
    QueryResult query(const std::string&) const;
private:
    // shared_ptr created to represent the input file in string vector form
    std::shared_ptr<std::vector<std::string>> file;
    
    // map of each word to the set of the lines in which that word appears
    // key is the word, the value is the line number on which the word appears
    // note the "using" declaration from above is used to improve legibility from...
    //
    // std::map<std::string, std::shared_ptr<std::set<std::vector<std::string>>::size_type>>> wm;
    //
    // or
    //
    // map<string,shared_ptr<set<vector<string>>::size_type>>> wm;
    //
    // if using namespaces
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    // friend member needed like in early chapters to print results
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    // "using" appears again to help with legibility (could write it in global scope)
    // typing it solely in TextQuery does not allow QueryResult to access it
    using line_no = std::vector<std::string>::size_type;
    
    // QueryResult constructor
    // takes 3 parameters - "sought, "lines", and "file"
    // i.e. check which lines (p) string "s" appears in our file's "(f) vector
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
private:
    // variables typically stored in private section of class
    // here we have the variables for our constructor
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};
