// Exercise 11.35:
/*
 Our program does no checking on the validity of either input file.
 In particular, it assumes that the rules in the transformation file are all sensible.
 What would happen if a line in that file has a key, one space, and then the end of the line?
 Predict the behavior and then check it against your version of the program.
 
 >> If a line in the map file has a key, one space, and then end-of-the-line then it will produce a runtime error
 >> Strangely, if we were to add another space between and the end-of-the-line, the programme would read the second space as the mapped string replacement
*/

#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iostream>

std::map<std::string, std::string> buildMap(std::ifstream &map_file)
{
    std::map<std::string, std::string> trans_map;
    std::string key;
    std::string value;
    
    while (map_file >> key && std::getline(map_file, value))
        if (value.size() > 1)
            // trans_map[key] = value.substr(1);
            trans_map.insert({key, value.substr(1)});
        else
            throw std::runtime_error("no rule for " + key);
    return trans_map;
}

const std::string &transform(const std::string &s, const std::map<std::string, std::string> &m)
{
    // the actual map work; the part is the heart of the programme
    auto map_it = m.find(s);
    
    // if this word is on the transformation map
    if (map_it != m.cend())
        // use the replacement word
        return map_it->second;
    else
        // otherwise return the original unchanged
        return s;
}

void word_transform(std::ifstream &map_file, std::ifstream &input)
{
    // store the transformations
    auto trans_map = buildMap(map_file);
    
    // hold each line from the inptu
    std::string text;
    
    // read a line of input
    while (std::getline(input, text)) {
        // read each word
        std::istringstream stream(text);
        std::string word;
        // controls whether a space is printed
        bool firstword = true;
        while (stream >> word) {
            if (firstword)
                firstword = false;
            else
                // prints a space between words
                std::cout << " ";
            
            // transform returns its first arguments or its first transformation
            std::cout << transform(word, trans_map);   // print the output
        }
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "No input files found – closing programme..." << std::endl;
        return -1;
    }
    
    if (argc > 3) {
        std::cerr << "Tom many aguments – closing programme..." << std::endl;
        return -1;
    }
    
    std::ifstream input(argv[1]), map_file(argv[2]);
    
    if (!input.is_open() && !map_file.is_open()) {
        std::cerr << "Could not open files – closing programme..." << std::endl;
        return -1;
    }
    
    // only need one real function for this main
    // take map_file and input from arguments
    word_transform(map_file, input);
    
    return 0;
}
