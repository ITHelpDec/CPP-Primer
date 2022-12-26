// Exercise 17.33:
/*
 Write a version of the word transformation program from § 11.3.6 (p. 440) that allows multiple transformations for a given word and randomly selects which transformation to apply.
*/

#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <random>

std::size_t randomIndex(const std::size_t &max) {
    static std::default_random_engine e(315);
    static std::uniform_int_distribution<std::size_t> u(0, max - 1);
    // std::cout << 0 << "-" << max - 1 << " (" << u(e) << ")" << std::endl;
    return u(e);
}


std::map<std::string, std::vector<std::string>> buildMap(std::ifstream &map_file) {
    std::map<std::string, std::vector<std::string>> trans_map;
    std::string key, values, value;
    
    while (map_file >> key && std::getline(map_file, values)) {
        std::istringstream iss(values);
        while (iss >> value) {
            if (value.size())
                trans_map[key].push_back(value);
            else
                throw std::runtime_error("no rule for " + key);
        }
    }
    
    return trans_map;
}

const std::string& transform(const std::string &s, const std::map<std::string, std::vector<std::string>> &m) {
    auto map_it = m.find(s);
    return map_it != m.cend() ? map_it->second[randomIndex(map_it->second.size())] : s;
}

void word_transform(std::ifstream &map_file, std::ifstream &input) {
    auto trans_map = buildMap(map_file);
    std::string text;
    while (std::getline(input, text)) {
        std::istringstream stream(text);
        std::string word;
         bool first_wood = true;
        while (stream >> word) {
            if (first_wood)
                first_wood = false;
            else
                std::cout << " ";
            std::cout << transform(word, trans_map);
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::ifstream map_file("word-transformation");
    
    if (!map_file) {
        std::cerr << "Unable to open map_file." << std::endl; return -1;
    } std::cout << "map_file opened successfully." << std::endl;
    
    std::ifstream input("input");
    
    if (!input) {
        std::cerr << "Unable to open input file.\n" << std::endl; return -1;
    } std::cout << "input file opened successfully.\n" << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    word_transform(map_file, input);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    input.close();
    map_file.close();
    
    if (map_file.is_open() && input.is_open()) {
        std::cerr << "\nUnable to open all files." << std::endl; return -1;
    } std::cout << "\nAll files closed successfully." << std::endl;
    
    return 0;
}
