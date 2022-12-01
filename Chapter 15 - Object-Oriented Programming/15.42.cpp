// Exercise 15.42:
/*
 Design and implement one of the following enhancements:
 (a) Print words only once per sentence rather than once per line.
 (b) Introduce a history system in which the user can refer to a previous query by number, possibly adding to it or combining it with another.
 (c) Allow the user to limit the results so that only matches in a given range of lines are displayed.
 
 >> All interesting concepts.
 >> History system (b) would be easy enough to implement using a vector to store where items have found in the input file i.e. c.find(s) != c.end()
 >> We could then decide if we want to print these results with numbers as references when prompting the user for input, and perhaps their line number. In that case we could use an unsorted_map<std::string, std::size_t> and set the std::size_t to ++smap.size() (provided we don't remove elements from the map)
*/
