// Exercise 10.30:
/*
 Use stream iterators, sort, and copy to
 (1) read a sequence of integers from the standard input,
 (2) sort them,
 (3) and then write them back to the standard output.
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
    std::cout << "sorted output: ";
    std::copy(ivec.begin(), ivec.end(), out_iter);
    
    std::cout << std::endl;
    
    return 0;
}

