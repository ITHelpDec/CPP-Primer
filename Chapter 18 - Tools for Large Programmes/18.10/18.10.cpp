// Exercise 18.10:
/*
 Write a program that uses the Sales_data addition operator on ob- jects that have differing ISBNs.
 Write two versions of the program: one that handles the exception and one that does not.
 Compare the behavior of the programs so that you become familiar with what happens when an uncaught exception occurs.
*/

#include "Sales_data.hpp"

void handles(Sales_data &book1, Sales_data &book2, Sales_data sum) {
    std::cout << "Attempting to add two different books.." << std::endl;
    std::cout << "book1: " << book1.isbn() << "\n"
              << "book2: " << book2.isbn() << "\n" <<std::endl;;
    
    try {
        sum = book1 + book2;
    } catch (const isbn_mismatch &e) {
        std::cerr << e.what() << ":\nleft isbn(" << e.left_ << ")\nright isbn(" << e.right_ << ")" << std::endl;
    }
}

void doesntHandle(Sales_data &book1, Sales_data &book2, Sales_data sum) {
    std::cout << "Attempting to add two different books.." << std::endl;
    std::cout << "book1: " << book1.isbn() << "\n"
              << "book2: " << book2.isbn() << "\n" <<std::endl;;
    
    sum = book1 + book2;
}

int main()
{
    Sales_data book1("123-456-789-X", 2, 10.00), book2("123-456-789-Y", 2, 10.00), sum;
    
    handles(book1, book2, sum);
    
    doesntHandle(book1, book2, sum);
    
    return 0;
}
