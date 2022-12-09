// Exercise 16.22:
/*
 Revise your TextQuery programs from § 12.3 (p. 484), so that the shared_ptr members use a DebugDelete as their deleter (§ 12.1.4, p. 468).
 
 // I don't really want to do this for all of the programmes
*/

#ifndef TextQuery_hpp
#define TextQuery_hpp

class QueryResult;

class TextQuery {
public:
    using line_no = std::size_t;
    
    TextQuery(std::ifstream&);
    
    QueryResult query(const std::string&) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    // it will look something like below, but this doesn't compile
    // std::shared_ptr<std::vector<std::string>, DebugDelete> file;
    
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
    // same goes for the below
    // std::map<std::string, std::shared_ptr<std::set<line_no>, DebugDelete>> wm;
    
    // we would then use the "new" command and "()" operator from DebuDelete with an object
    // ... = wm(new std::string, new std::set<line_no>, DebugDelete()>);
    
    
};

#endif
