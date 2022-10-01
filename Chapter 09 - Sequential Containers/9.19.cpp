// Exercise 9.19:
/*
 Rewrite the program from the previous exercise to use a list. List the changes you needed to make.
*/

#include <string>
// (1) #include <deque>
#include <list>
#include <iostream>

int main()
{
    // create deque to store elements
    // (2) std::deque<std::string> sdeque;
    std::list<std::string> slist;
    
    // create strings to store stream and each word
    std::string word;
    
    // read from standard output (std::cin)
    while (std::cin >> word) {
        slist.push_back(word);
    }
    
    // (3) for (std::deque<std::string>::const_iterator pos = sdeque.begin(); pos != sdeque.end(); ++pos) {
    for (std::list<std::string>::const_iterator pos = slist.begin(); pos != slist.end(); ++pos) {
        std::cout << *pos << " ";
    }
    
    return 0;
}
