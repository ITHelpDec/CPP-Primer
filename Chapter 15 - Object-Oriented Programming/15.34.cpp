// Exercise 15.34:
/*
 For the expression built in Figure 15.3 (p. 638):
 
 (a) List the constructors executed in processing that expression.
 (b) List the calls to rep that are made from cout<< q.
 (c) List the calls to eval made from q.eval().
 
 // Query q = Query("fiery") & Query("bird") | Query("wind");
 
 >> (a) Constructors
 // Query::Query(const std::string &s), where s is "fiery", "bird" or "wind"
 // WordQuery::WordQuery(const std::string &s) as above
 
 // AndQuery::AndQuery(const Query &left, const Query &right)
 // BinaryQuery::BinaryQuery(const Query &l, const Query &r, std::string s)
 // Query::Query(std::shared_ptr<Query_base> query) for "fiery"
 // Query::Query(std::shared_ptr<Query_base> query) for "bird"
 
 // OrQuery::OrQuery(const Query &left, const Query &right)
 // BinaryQuery::BinaryQuery(const Query &l, const Query &r, std::string s)
 // Query::Query(std::shared_ptr<Query_base> query) for "fiery"
 // Query::Query(std::shared_ptr<Query_base> query) for "bird"
 
 >> (b) rep()
 // query.rep() instead operator<<()
 // q->rep() inside member function rep()
 
 // OrQuery::rep(), which is inherited from BinaryQuery
 // Query::rep() for lhs and rhs
 // // lhs: AndQuery
 // // rhs: WordQuery::WordQuery::rep()
 // // // returns query_word("wind")
 
 // AndQuery::rep(), which is inherited from BinaryQuery
 // BinaryQuery::rep()
 // // lhs: WordQuery::rep()
 // // // returns query_word("bird")
 // // rhs: WordQuery::rep()
 // // // returns query_word("fiery")
 
 >> (c) eval()
 // q.eval()
 // q->rep(), where "q" is a pointer to OrQuery
 // QueryResult eval(const TextQuery&) const override (not yet defined)
 
 (many thanks to Mooophy for concise explanations)

*/
