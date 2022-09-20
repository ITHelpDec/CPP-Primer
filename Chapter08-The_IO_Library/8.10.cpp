// Exercise 8.10:
/*
 Write a program to store each line from a file in a vector<string>.
 Now use an istringstream to read each element from the vector a word at a time.
 
 >> Would have preferred to create a function to read the file and store as a vector, then output the stream, as opposed to writing it all in main
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

int main(int argc, char **argv)
{
    // check there are enough arguments
    if (argc < 2) {
        std::cerr << "No file provided in arguments." << std::endl;
        return -1;
    }
    
    if (argc > 2) {
        std::cerr << "Too many arguments provided – please only provide file we are reading from." << std::endl;
        return -1;
    }
    
    // "./main 8.10.txt"
    // attempt to open file from argument line
    std::ifstream in(argv[1]);
    
    // return error if file not found
    if (!in) {
        std::cerr << "File not found!" << std::endl;
        return -1;
    }
    
    // carry on with function
    std::cout << "File opened successfully" << std::endl;
    
    // create string for each line and vector to store strings
    std::string line;
    std::vector<std::string> svec;
    
    // read file and add lines to vector
    while (std::getline(in, line))
        svec.push_back(line);
    
    in.close();
    if (!in.is_open())
        std::cout << "File closed successfully." << std::endl;
    
    for (auto &e : svec) {
        std::istringstream iss(e);
//        for (std::string word; iss >> word; std::cout << word << " ")
//        {
//            // read:
//            // (1) create a string to store words
//            // (2) for as long as there are words to read in the stream
//            // (3) output the words to console
//        }
        
        // or use a while loop, like the xample in the book
        // create a string to store each word of the
        std::string word;
        while (iss >> word)
            std::cout << word << " ";
    }
    std::cout << std::endl;
    
    return 0;
}
