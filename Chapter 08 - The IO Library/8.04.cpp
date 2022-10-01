// Exercise 8.4:
/*
 Write a function to open a file for input and read its contents into a
 vector of strings, storing each line as a separate element in the vector.
 
 // 8.4.txt
 Hello
 My
 Name
 Is
 Dog
 Woof
 Woof
 
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
    std::ifstream in(filename); // construct
    
    // check the file opened properly
    if (in) {
        // Announce success
        std::cout << "Reading contents of file..." << std::endl;
        
        // iterate through each line in the file using getline() and create unique elements in the vector
        for (std::string line; std::getline(in, line); /* no increment needed */) {
            // add each string to the vector
            svec.push_back(line);
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
    std::string filename = "8.4.txt";
    
    // create local result and
    for (auto &e : read(filename))
        std::cout << e << " ";
    
    std::cout << std::endl;
    return 0;
}
