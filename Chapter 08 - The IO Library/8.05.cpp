// Exercise 8.5:
/*
 Rewrite the previous program to store each word in a separate element.
 
 // 8.5.txt
 Hello
 My Name Is Dog
 Woof Woof
 
 Output:
 Reading contents of file...
 Contents stored successfully.
 Hello My Name Is Dog Woof Woof
 Program ended with exit code: 0
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// create function of type vector<string> that will read a given file
std::vector<std::string> read(const std::string &filename)
{
    // create an empty vector to store strings when reading file
    std::vector<std::string> svec;
    
    // construct an ifstream and open the given file
    std::ifstream in(filename);
    
    // check the file opened properly
    if (in) {
        // Announce success
        std::cout << "Reading contents of file..." << std::endl;
        
        // iterate through each word in the file using the ifstream and create unique elements in the vector
        for (std::string word; in >> word ; ) {
            // add each string to the vector
            svec.push_back(word);
        }
    } else {
        // Throw error if file not found
        std::cerr << "Unable to open file." << std::endl;
    }
    
    // close file
    in.close();
    std::cout << "Contents stored successfully." << std::endl;
    
    return svec;
}

int main()
{
    // set filename
    std::string filename = "8.5.txt";
    
    // create local result and
    for (auto &e : read(filename))
        std::cout << e << " ";
    
    std::cout << std::endl;
    return 0;
}
