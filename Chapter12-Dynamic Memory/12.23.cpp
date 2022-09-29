// Exercise 12.23:
/*
 Write a program to concatenate two string literals, putting the result in a dynamically allocated array of char.
 Write a program to concatenate two library strings that have the same value as the literals used in the first program.
 
 >> EDIT: in hindsight, a string literal is
 // const char *sl = "Hello, ";
 >> May try again, but for now it works
*/

#include <string>
#include <iostream>

void concatStrLit(const std::string &sl1, const std::string &&sl2)
{
    // create dynamic array
    char *pca = new char[sl1.size() + sl2.size() + 1];
    
    // iterate through first string
    for (size_t i = 0; i != sl1.size(); ++i)
        pca[i] = sl1[i];

    // add second string to rest of array
    for (size_t j = sl1.size(); j != (sl1.size() + sl2.size()); ++j)
        pca[j] = sl2[j-sl2.size()-1];
    
    // print final result
    std::cout << "Final result:\n\"";
    for (int i = 0; i != (sl1.size() + sl2.size()); ++i) {
        std::cout << pca[i];
    } std::cout << "\"\n" << std::endl;
    
    // show individual characters
    std::cout << "Final result in characters:\n";
    for (int i = 0; i != (sl1.size() + sl2.size()); ++i) {
        std::cout << "\'" << pca[i] << "\' ";
    } std::cout << "\n" << std::endl;
    
    // remember to delete dynamic array
    delete [] pca;
}

void concatLibStr(const std::string &ls1, const std::string &ls2)
{
    std::cout << "Final result with strings:\n";
    std::cout << "\"" << ls1 + ls2 << "\"" << std::endl;
}

int main()
{
    concatStrLit("Hello, ", "world!");
    
    std::string ls1 = "Hello, ", ls2 = "world!";
    concatLibStr(ls1, ls2);
    
    return 0;
}
