// Exercise 18.12:
/*
 Organize the programs you have written to answer the questions in each chapter into their own namespaces.
 That is, namespace chapter15 would contain code for the Query programs and chapter10 would contain the TextQuery code.
 Using this structure, compile the Query code examples.
 
 >> I had modified a master version of each main programme throughout each chapter to avoid having multiple copies.
 
 >> Had the author known they wanted to pose an exercise like this, it would have been more helpful to phrase the earlier questions without the word "modify"
 
 >> e.g. "Create a new version of Query using your most recent version as a template, as we will want to make of use all of these versions collectively in later chapters".
 
 >> I've created a generic namespace programme below to show implementation of the concerpt, regardless.
 
*/

#include <string>
#include <iostream>
#include <iomanip>

struct Dog {
    std::string bark = "woof!";
};

namespace chapter6 {
struct Dog {
    std::string bark = "woof, woof!!";
};
} // chapter6

namespace chapter18 {
struct Dog {
    std::string bark = "woof, woof, woof!!!";
};
} // chapter18

int main()
{
    std::cout << "global:    " << Dog().bark << std::endl;
    std::cout << "chapter6:  " << chapter6::Dog().bark << std::endl;
    std::cout << "chapter18: " << chapter18::Dog().bark << std::endl;
    
    return 0;
}
