// Exercise 9.39:
/*
 Explain what the following program fragment does:
 
 vector<string> svec;
 svec.reserve(1024);
 string word;
 
 while (cin >> word)
    svec.push_back(word);
 svec.resize(svec.size() + svec.size()/2);
 
*/

#include <vector>
#include <string>
#include <iostream>

int main()
{
    // create empty vector of strings
    std::vector<std::string> svec;
    
    // allocate memory for 1024 elements
    svec.reserve(3);
    
    std::cout << svec.size() << " " << svec.capacity() << std::endl;
    
    // create word string for loop
    std::string word;
    
    // for as many words that are input...
    while (std::cin >> word)
        // add the word to the vector until end-of-file
        svec.push_back(word);
    // if 20 elements are recorded, the size is now 30, but the capacity remains unchanged
    svec.resize(svec.size() + svec.size()/2);
    
    std::cout << svec.size() << " " << svec.capacity() << std::endl;
    
    return 0;
}
