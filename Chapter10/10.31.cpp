// Exercise 10.31:
/*
 Update the program from the previous exercise so that it prints only the unique elements.
 Your program should use unqiue_copy (§ 10.4.1, p. 403).
*/

#include <iterator>
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    // create istream_iterators for std::cin and eof
    std::cout << "input: ";
    std::istream_iterator<int> in_iter(std::cin), eof;
    
    // store standard input into local vector
    std::vector<int> ivec(in_iter, eof);
    
    // sort vector created from input stream
    std::sort(ivec.begin(), ivec.end());
    
    // create iterator for standard output
    std::ostream_iterator<int> out_iter(std::cout, " ");
    
    // use copy to print results using iterators
    std::cout << "output: ";
    std::unique_copy(ivec.begin(), ivec.end(), out_iter);
    
    std::cout << "(sorted without duplicates)" << std::endl;
    
    return 0;
}
