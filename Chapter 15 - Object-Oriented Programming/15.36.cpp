// Exercise 15.36:
/*
 Put print statements in the constructors and rep members and run your code to check your answers to (a) and (b) from the first exercise.
 
 >> (a) Query q = Query("fiery") & Query("bird") | Query("wind");
 
 WordQuery::WordQuery(std::string&)
 Query::Query(const std::string &s) => "wind"
 WordQuery::WordQuery(std::string&)
 Query::Query(const std::string&) => "bird"
 WordQuery::WordQuery(std::string&)
 Query::Query(const std::string&) => "fiery"
 BinaryQuery::BinaryQuery()
 AndQuery::AndQuery()
 Query::Query(std::shared_ptr<Query_base> query)
 BinaryQuery::BinaryQuery()
 OrQuery::OrQuery
 Query::Query(std::shared_ptr<Query_base> query)
 
 >> (b) std::cout << q <<std::endl;
 
 Query::rep()
 BinaryQuery::rep()
 Query::rep()
 WodQuery::rep()
 Query::rep()
 BinaryQuery::rep()
 Query::rep()
 WodQuery::rep()
 Query::rep()
 WodQuery::rep()
 
*/
