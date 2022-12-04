#include "Blob.hpp"
#include "BlobPtr.hpp"

#include <iostream>

int main()
{
    Blob<int> blob1;
    Blob<int> blob2 = { 0, 2, 2 };
    
    std::cout << "blob1: ";
    for (int i = 0; i != blob1.size(); ++i)
    { std::cout << blob1[i] << " "; } std::cout << std::endl;
    
    std::cout << "blob2: ";
    for (int i = 0; i != blob2.size(); ++i)
    { std::cout << blob2[i] << " "; } std::cout << std::endl << std::endl;
    
    std::cout << "blob1 has " << blob1.size() << " elements." << std::endl;
    std::cout << "blob2 has " << blob2.size() << " elements.\n" << std::endl;
    
    std::cout << "Adding 2 elements to blob1...\n";
    int x = 0;
    blob1.push_back(x);
    blob1.push_back(1);
    
    std::cout << "blob1 now has " << blob1.size() << " elements.\n" << std::endl;
    
    std::cout << "front(): is " << blob1.front() << " == " << blob2.front() << " ?: ";
    std::cout << (blob1.front() == blob2.front() ? "Yes." : "No.") << std::endl;
    
    std::cout << "back():  is " << blob1.back() << " == " << blob2.back() << " ?: ";
    std::cout << (blob1.back() == blob2.back() ? "Yes." : "No.") << std::endl << std::endl;
    
    std::cout << "Is blob1 == blob2 ?: ";
    std::cout << (blob1 == blob2 ? "Yes." : "No.") << std::endl << std::endl;
    
    std::cout << "Removing an element from blob2...\n";
    blob2.pop_back();
    std::cout << "Is blob1 == blob2 now ?: ";
    std::cout << (blob1 == blob2 ? "Yes." : "No.") << std::endl << std::endl;
    
    std::cout << "Changing blob2.back() to 1...\n";
    blob2.back() = 1;
    std::cout << "Is blob1 == blob2 now ?: ";
    std::cout << (blob1 == blob2 ? "Yes." : "No.") << std::endl << std::endl;
    
    std::cout << "blob1: ";
    for (int i = 0; i != blob1.size(); ++i)
    { std::cout << blob1[i] << " "; } std::cout << std::endl;
    
    std::cout << "blob2: ";
    for (int i = 0; i != blob2.size(); ++i)
    { std::cout << blob2[i] << " "; } std::cout << std::endl << std::endl;
    
    return 0;
}
