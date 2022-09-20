// Exercise 9.18:
/*
 Write a program to read a sequence of strings from the standard input into a deque.
 Use iterators to write a loop to print the elements in the deque.
*/

#include <string>
#include <deque>
#include <iostream>

int main()
{
    // create empty deque to store elements
    std::deque<std::string> sdeque;
    
    // create empty string to store each element temporarily
    std::string word;
    
    // read from standard output (std::cin) and add strings to deque
    while (std::cin >> word) {
        sdeque.push_back(word);
    }
    
    // use .begin() and .end() iterators to loop through elements of sdeque
    for (std::deque<std::string>::const_iterator pos = sdeque.begin(); pos != sdeque.end(); ++pos) {
        std::cout << *pos << " ";
    }
    
    return 0;
}
