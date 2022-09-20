// Exercise 10.12:
/*
 Write a function named compareIsbn that compares the isbn() members of two Sales_data objects.
 Use that function to sort a vector that holds Sales_data objects.
*/

#include <vector>
#include <iostream>
#include <algorithm>

struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    std::string bookName;
};

bool compareIsbn(const Sales_data &item1, const Sales_data &item2)
{
    return item1.bookNo > item2.bookNo;
}

int main()
{
    // create examples of 5th and 6th edition C++ Primer books
    Sales_data book1 = { "9780321714114", 1, 33.13, "5th Edition" };
    Sales_data book2 = { "9780135161791", 1, 45.75, "6th Edition" };
    Sales_data book3 = { "9780321714114", 4, 33.13, "5th Edition" };
    
    // add to vector
    std::vector<Sales_data> sdvec = { book1, book2, book3 };
    
    // Print intial results
    std::cout << "Printing vector: " << std::endl;
    for (const auto &e : sdvec)
        std::cout << e.bookNo << " " << e.revenue << " " << e.units_sold << " (" << e.bookName << ")" << std::endl;
    std::cout << std::endl;
    
    // sort by ISBN using compareIsbn function as a argument (again, without parentheses)
    std::cout << "Sorting Sales_data.." << std::endl << std::endl;
    std::sort(sdvec.begin(), sdvec.end(), compareIsbn);
    
    // print final results
    std::cout << "Printing results: " << std::endl;
    for (const auto &e : sdvec)
        std::cout << e.bookNo << " " << e.revenue << " " << e.units_sold << " (" << e.bookName << ")" << std::endl;
    std::cout << std::endl;
    
    return 0;
}
