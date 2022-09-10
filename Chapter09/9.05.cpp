// Exercise 9.05:
/*
 Rewrite the previous program to return an iterator to the requested ele- ment.
 Note that the program must handle the case where the element is not found.
*/

#include <vector>
#include <iostream>

// function must now return iterator instad of bool
// bool findNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end, int x) {
std::vector<int>::iterator findNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end, int x) {
    for (auto pos = begin; pos != end; ++pos) {
        if (*pos == x)
            return pos;
    }
    return end;
}

int main()
{
    // create test vector
    std::vector<int> ivec = {0, 2, 4, 6, 8};
    
    // number you want to find
    int testNum = 6;
    
    // abbreviate the function to make it easier to read in loops
    auto test = findNumber(ivec.begin(), ivec.end(), testNum);
    
    // first check for failure, then print position of success in vector
    if(test == ivec.end())
        std::cout << testNum << " was not found in the list." << std::endl;
    else
        std::cout << testNum << " was element number " << (test - ivec.begin()) + 1 << " in the list (ivec[" << test - ivec.begin() << "])" << std::endl;
        
    return 0;
}
/*
 
 Again, using stringstream from chapter 8
 
#include <sstream>

int main ()
{
    std::string line;               // create string to store input
    std::getline(std::cin, line);   // take a line of user inputand store it to stream
    std::istringstream iss(line);   // bind contents of str to iss
    
    int num;                        // variable we will use to create unique elements in vector
    std::vector<int> ivec;          // create vector to store info in string stream
    
    while (iss >> num)              // for as long as there are numbers to read from the string stream
        ivec.push_back(num);        // add numbers as unique elements to the vector
    
    int testNum;                    // create variable for the number we want to find
    
    std::cout << "What number do you want to find?: ";
    
    std::cin >>  testNum;           // ask user what number they wantt o find
    
    auto test = findNumber(ivec.begin(), ivec.end(), testNum);
    
    if(test == ivec.end())
        std::cout << testNum << " was not found in the list." << std::endl;
    else
        std::cout << testNum << " was element number " << (test - ivec.begin()) + 1 << " in the list (ivec[" << test - ivec.begin() << "])" << std::endl;
        
    return 0;
}
*/
