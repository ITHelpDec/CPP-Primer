// Exercise 12.24:
/*
 Write a program that reads a string from the standard input into a dynamically allocated character array.
 Describe how your program handles varying size inputs.
 Test your program by giving it a string of data that is longer than the array size you’ve allocated.
*/

#include <string>
#include <iostream>

int main()
{
    std::cout << "Please input a string: ";
    std::string s1;
    std::cin >> s1;
    
    std::cout << "Current size of array is " << s1.size() << std::endl;
    char *pca1 = new char[s1.size()];
    
    for (int i = 0; i != s1.size(); ++i)
        pca1[i] = s1[i];
    
    for (int i = 0; i != s1.size(); ++i) {
        std::cout << pca1[i];
    } std::cout << std::endl;
    
    for (int i = 0; i != s1.size(); ++i) {
        std::cout << "\'" << pca1[i] << "\' ";
    } std::cout << std::endl;
    
    std::cout << "Attempting to insert string larger than array...\n";
    std::string s2(s1 + s1);
    
    if (s2.size() > s1.size()) {
        std::cerr << "s2 (of size " << s2.size() << ") is too big for array (of size " << s1.size() << ")" << std::endl;
        return -1;
    }
    
    delete [] pca1;
    pca1 = nullptr;
    
    return 0;
}
