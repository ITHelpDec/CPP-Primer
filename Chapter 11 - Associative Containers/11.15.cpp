// Exercise 11.15:
/*
 What are the mapped_type, key_type, and value_type of a map from int to vector<int>?
*/

// ::mapped_type is std::vector<int>
std::map<int, std::vector<int>>::mapped_type

// ::key_type is int
std::map<int, std::vector<int>>::key_type

// ::value_type is std::pair<int, std::vector<int>>
std::map<int, std::vector<int>>::value_type
