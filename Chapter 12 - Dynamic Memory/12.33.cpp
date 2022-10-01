// Exercise 12.33:
/*
 In Chapter 15 we’ll extend our query system and will need some additional members in the QueryResult class.
 Add members named begin and end that return iterators into the set of line numbers returned by a given query,
 and a member named get_file that returns a shared_ptr to the file in the QueryResult object.
*/

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    using line_no = StrBlob::size_type;
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<StrBlob> f) : sought(s), lines(p), file(f) { }
    
    std::shared_ptr<std::ifstream> get_file() { return file; }
    
    std::set<line_no>::iterator begin() { return line_no->begin(); }
    std::set<line_no>::iterator end() { return line_no->end(); }
    
    std::set<line_no>::const_iterator begin() { return line_no->cbegin(); }
    std::set<line_no>::const_iterator cend() { return line_no->cend(); }
    
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    // std::shared_ptr<std::vector<std::string>> file;
    std::shared_ptr<StrBlob> file;
};
