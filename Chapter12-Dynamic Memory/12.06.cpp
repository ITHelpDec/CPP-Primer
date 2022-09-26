// Exercise 12.06:
/*
 Write a function that returns a dynamically allocated vector of ints.
 Pass that vector to another function that reads the standard input to give values to the elements.
 Pass the vector to another function to print the values that were read.
 Remember to delete the vector at the appropriate time.
*/

#include <vector>
#include <iostream>

std::vector<int>* createDynamicVec()
{
    return new std::vector<int>;
}

void inputVec(std::vector<int>* &daivec)
{
    int x;
    std::cout << "Please input a series of integers: ";
    while (std::cin >> x)
        daivec->push_back(x);
}

void printVec(std::vector<int>* &daivec)
{
    std::cout << "Printing dynamically allocated vector<int>: ";
    for (const auto &e : *daivec)
        std::cout << e << " ";
    std::cout << std::endl;
}

void deleteVec(std::vector<int>* &daivec)
{
    std::cout << "daivec = " << daivec << ", *daivec = ( ";
    for (const auto &e : *daivec)
        std::cout << e << " ";
    std::cout << ")" << std::endl;
    
    std::cout << "Deleting daivec..." << std::endl;
    delete daivec;
    
    std::cout << "After deletion:" << std::endl;
    std::cout << "daivec = " << daivec << ", *daivec = ( ";
    for (const auto &e : *daivec)
        std::cout << e << " ";
    std::cout << ")" << std::endl;
    
    std::cout << "Setting to nullptr..." << std::endl;
    daivec = nullptr;
    
    std::cout << "After nullptr:" << std::endl;
    std::cout << "daivec = " << daivec << " (*daivec will produce errors)";
    std::cout <<std::endl;
}

void dynamicVectorProgramme()
{
    // create
    std::vector<int> *daivec = createDynamicVec();
    
    // read
    inputVec(daivec);
    
    // print
    printVec(daivec);
    
    // delete
    deleteVec(daivec);
}

int main()
{
    dynamicVectorProgramme();
 
    return 0;
}
