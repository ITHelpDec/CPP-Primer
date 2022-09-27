// Exercise 12.16:
/*
 Compilers don’t always give easy-to-understand error messages if we attempt to copy or assign a unique_ptr.
 Write a program that contains these errors to see how your compiler diagnoses them.
*/

#include <iostream>
#include <memory>
#include <string>

int main()
{
    // creating a unique_ptr
    std::unique_ptr<std::string> p1(new std::string("Stegosaurus"));
    std::cout << "p1: " << p1 << ", *p1: " << *p1 << std::endl;
    
    // attempting to copy
    // "Call to implicitly-deleted copy constructor of 'std::unique_ptr<std::string>' (aka 'unique_ptr<basic_string<char, char_traits<char>, allocator<char> > >')""
    // std::unique_ptr<std::string> p2(p1);

    // "No viable conversion from 'std::unique_ptr<std::string>' (aka 'unique_ptr<basic_string<char, char_traits<char>, allocator<char> > >') to 'std::string' (aka 'basic_string<char, char_traits<char>, allocator<char> >')"
    // std::string p3 = p1;
    
    return 0;
}
