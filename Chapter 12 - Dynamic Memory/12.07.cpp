// Exercise 12.07:
/*
 Redo the previous exercise, this time using shared_ptr.
*/

#include <vector>
#include <iostream>
#include <memory>

// std::vector<int>>* createDynamicVec()
std::shared_ptr<std::vector<int>> createDynamicVec()
{
    // return new std::vector<int>;
    return std::make_shared<std::vector<int>>();
}

// no longer referring to alias
// void inputVec(std::vector<int>>* &spivec)
void inputVec(std::shared_ptr<std::vector<int>> spivec)
{
    int x;
    std::cout << "Please input a series of integers: ";
    while (std::cin >> x)
        spivec->push_back(x);
}

// void printVec(std::vector<int>>* &spivec)
void printVec(std::shared_ptr<std::vector<int>> spivec)
{
    std::cout << "Printing dynamically allocated vector<int>: ";
    for (const auto &e : *spivec)
        std::cout << e << " ";
    std::cout << std::endl;
}

/*
// no longer need to worry about deletion with shared pointers
void deleteVec(std::shared_ptr<std::vector<int>> &spivec)
{
    std::cout << "spivec = " << spivec << ", *daivec = ( ";
    for (const auto &e : *spivec)
        std::cout << e << " ";
    std::cout << ")" << std::endl;
    
    std::cout << "Deleting spivec..." << std::endl;
    delete spivec;
    
    std::cout << "After deletion:" << std::endl;
    std::cout << "spivec = " << spivec << ", *spivec = ( ";
    for (const auto &e : *spivec)
        std::cout << e << " ";
    std::cout << ")" << std::endl;
    
    std::cout << "Setting to nullptr..." << std::endl;
    spivec = nullptr;
    
    std::cout << "After nullptr:" << std::endl;
    std::cout << "spivec = " << spivec << " (*spivec will produce errors)";
    std::cout <<std::endl;
}*/

void dynamicVectorProgramme()
{
    // create (only exists within scope of programme
    std::shared_ptr<std::vector<int>> spivec = createDynamicVec();
    
    // read
    inputVec(spivec);
    
    // print
    printVec(spivec);
        
    // delete not ndeeded
    // deleteVec(spivec);
}

int main()
{
    dynamicVectorProgramme();
    
    return 0;
}
