// Exercise 12.31:
/*
 Rewrite the TextQuery and QueryResult classes to use a StrBlob instead of a vector<string> to hold the input file.
 
 >> Basically, every instance of...
 // std::vector<std::string>>
 >> ...becomes...
 // StrBlob
 
 >> Won't expand on changes needed in individual members and functions
 
*/

class TextQuery {
public:
    // // using line_no = std::vector<std::string>::size_type;
    using line_no = StrBlob::size_type;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const;
private:
    // std::shared_ptr<std::vector<std::string>> file;
    std::shared_ptr<StrBlob> file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult {
    friend std::ostream &print(std::ostream&, const QueryResult&);
public:
    // using line_no = std::vector<std::string>::size_type;
    using line_no = StrBlob::size_type;
    // QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
    QueryResult(std::string s, std::shared_ptr<std::set<line_no>> p, std::shared_ptr<StrBlob> f) : sought(s), lines(p), file(f) { }
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    // std::shared_ptr<std::vector<std::string>> file;
    std::shared_ptr<StrBlob> file;
};
