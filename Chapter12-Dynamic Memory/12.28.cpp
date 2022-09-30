// Exercise 12.28:
/*
 Write a program to implement text queries without defining classes to manage the data.
 Your program should take a file and interact with a user to query for words in that file.
 Use vector, map, and set containers to hold the data for the file and to generate the results for the queries.
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>

void implementTextQuery(std::string &query, std::string &file_name)
{
    std::ifstream file(file_name);
    
    if (!file.is_open()) {
        std::cerr << "Couldn't open file..." << std::endl;
        return;
    }
    
    // declare vector and map that we will use to store info
    // (1) create vector to hold each line of the file
    std::vector<std::string> input_vec;
    
    // (2) create a map with keys and values – the key will be "query"; the value will be set of lines where "query" appears
    //
    // std::vector<std::string>> is where everything is being stored
    // we can use std::vector<std::string>>::size_type as a numeric indicator for the vector
    // we can take advantage of "using" to simplify this code to "lines"
    // so, instead of writing a set of our line numbers like...
    // "std::set<std::vector<std::string>::size_type>", we can just write "lines"
    using lines = std::set<std::vector<std::string>::size_type>;
    std::map<std::string, lines> word_map;
    
    // (3) populate containers, starting with each line
    // have a variable to store a string of each line
    std::string line;
    // (4) create a variable to remember the line number we are on
    // we will use this to populate our map's values i.e. the set
    std::size_t line_no = 0;
    // (5) for as many lines are in our file
    while (std::getline(file, line)) {
        // (6) add each line as a new element to our vector
        input_vec.push_back(line);
        // (7) bind the contents of line into an istringstream
        std::istringstream iss(line);
        // (8) push the words from the istringstream into "word", one word at a time
        std::string word;
        while (iss >> word) {
            // (8) subscript allows us to look for a word in the map
            // if it exists, it will insert the line_no to our set
            // if it doesn't exist, it will be created as a new key before then inserting the corresponding value
            word_map[word].insert(line_no);
        }
        ++line_no;
    }
    
    // (9) close the file now that we have filled our containers
    file.close();
    
    // (10) provided we can find it...
    if (word_map.find(query) != word_map.end()) {
        // announce how many lines have "query" in them and print them as per the format from the chapter
        // (finding actual occurences will involve tweaking the code e.g. if the word appears multiple times in the line)
        std::cout << "\'" << query << "\' was found on " << word_map.find(query)->second.size() << ((word_map.find(query)->second.size() == 1) ? " line." : " different lines.") << std::endl;
        // (11) iterate through every line number for all successful hits in finding "query"
        for (const auto &e : word_map.find(query)->second) {
            std::cout << "\t(line " << e + 1 << ")\t\"" << input_vec[e] << "\"" << std::endl;
            } std::cout << std::endl;
    } else {
        // (12) account for not finding the word as well
        std::cerr << "\'" << query << "\' was not found in this file." << std::endl;
        return;
    }
}

// this structure "works", but I can understand why classes would be useful in tidying up order / workflow
// in hindight I would:
// (1) open file and populate containers
// (2) ask user for a query item
// (3) return the results

int main()
{
    // word we want to search for
    std::cout << "What word would you like to search for?: ";
    std::string search_item;
    std::cin >> search_item;
    
    // file we want to search in
    std::string file_name = "./12.28_in.txt";
    
    // show me all the lines where this word appears in this file
    implementTextQuery(search_item, file_name);
    
    return 0;
}
