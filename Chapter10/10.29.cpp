// Exercise 10.29:
/*
 Write a program using stream iterators to read a text file into a vector of strings.
*/

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>

void read_into_vec()
{
    // create vector to store strings
    std::vector<std::string> svec;
    
    // open file
    std::ifstream in("10.29.txt");
    
    // exit if unable to access file (maybe better suited for main?)
    if(!in.is_open()) {
        std::cerr << "Couldn't open file – closing programme..." << std::endl;
        return;
    }
    
    std::cout << "File found – beginning programme..." << std::endl;
    
    // read strings from file
    std::istream_iterator<std::string> str_it(in);
    
    // create eof variable for while comparison (iterator is empty)
    std::istream_iterator<std::string> eof;
    
    // for as long as the stream isn't empty, add to the vector
    while (str_it != eof)
        svec.push_back(*str_it++);
    
    // can also write the following as shorthand – savea few lines of code
    // std::vector<std::string> svec(str_it, eof);
    
    // print the results
    for (const auto &e : svec) std::cout << e << " ";
    
    in.close();
}

int main()
{
    read_into_vec();
    
    return 0;
}
