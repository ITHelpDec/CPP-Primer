// Exercise 10.32:
/*
 Rewrite the bookstore problem from § 1.6 (p. 24) using a vector to hold the transactions and various algorithms to do the processing.
 Use sort with your compareIsbn function from § 10.3.1 (p. 387) to arrange the transactions in order, and then use find and accumulate to do the sum.
 
 >> !!! THE FOR LOOP USED BELOW IS A CONCEPT WORTH MEMORISING !!!
 
0-201-78345-X 3 19.99
0-201-78345-X 2 19.99
0-201-70353-X 4 24.99
0-201-78349-X 3 39.99
0-201-78315-X 6 19.99
0-201-78579-X 1 79.99
0-201-68345-X 12 9.99
 
*/

#include <iostream>
#include "Sales_item.h"
#include <iterator>
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>

int main()
{
    // create empty Sales_item for total
    Sales_item total;
    
    // create input stream iterators for standard input and eof
    std::cout << "in:\n";
    std::istream_iterator<Sales_item> in_iter(std::cin), eof;
    
    // if no input, throw error and exit programme
    if (in_iter == eof) {
        std::cerr << "No data entered – closing programme..." << std::endl;
        return -1;
    }
    
    // create vector to hold transactions
    std::vector<Sales_item> trans(in_iter, eof);
    
    // sort by ISBN using lambda function
    std::sort(trans.begin(), trans.end(), [] (Sales_item &item1, Sales_item &item2) { return item1.isbn() < item2.isbn(); } );
    
    // create output iterator
    std::ostream_iterator<Sales_item> out_iter(std::cout, "\n");
    
    // print sorted list using output iterator
    std::cout << "\nsorted:\n";
    std::copy(trans.begin(), trans.end(), out_iter);
    
    // print accumulate
    std::cout << "\naccumulated:\n";
    
    // we need two iterators for our next loop
    // (1) when a particular ISBN appears for the first time
    // (2) when the next unique ISBN appears
    std::vector<Sales_item>::iterator ISBN_first_inst, next_new_ISBN;
    
    // (1) - start from the beginning of the transactions
    // (2) - run as long as we haven't reached eof
    // (3) - restart loop from next unique record by setting ISBN_first_inst = next_new_ISBN
    for (ISBN_first_inst = trans.begin(); ISBN_first_inst != trans.end(); ISBN_first_inst = next_new_ISBN) {
        
        // use find_if to locate position where ISBN's no longer match
        next_new_ISBN = std::find_if(ISBN_first_inst, trans.end(), [ISBN_first_inst] (const Sales_item &item) { return item.isbn() != ISBN_first_inst->isbn(); } );
        
        // accumulate all objects from _1 to _2 that share the same ISBN
        // ... then use out_iter to push result to std::cout
        out_iter = std::accumulate(ISBN_first_inst, next_new_ISBN, Sales_item(ISBN_first_inst->isbn()));
    }
        
    std::cout << std::endl;

    return 0;
}
