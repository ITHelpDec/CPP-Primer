// Exercise 9.04:
/*
 Write a function that takes a pair of iterators to a vector<int> and an int value.
 Look for that value in the range and return a bool indicating whether it was found.
*/

#include <vector>
#include <iostream>

// bool function takes pair of iterators and int value
bool findNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end, int x) {
    
    for (auto iter = begin; iter != end; ++iter) {
        if (*iter == x)
        {
            return true;
        }
    }
    return false;
}


int main()
{
    // create test vector
    std::vector<int> ivec = {0, 2, 4, 6, 8};
    
    // number you want to find
    int testNum = 5;
    
    // find the number
    if(findNumber(ivec.begin(), ivec.end(), testNum))
        std::cout << testNum << " exists in your vector." << std::endl;
    else {
        std::cerr << "Could not find " << testNum << " in your vector." << std::endl;
        return 1;
    }
    
    
    return 0;
}

/*
 Can also use stringstream from previous chapter

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
    
    if (findNumber(ivec.begin(), ivec.end(), testNum))
        std::cout << "We found " << testNum << "!" << std::endl;
    else
        std::cerr << "We could not find " << testNum << "..." << std::endl;
    
    return 0;
}
*/
