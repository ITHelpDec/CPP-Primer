// Exercise 10.33: (vector edition)
/*
 Write a program that takes the names of an input file and two output files.
 
 The input file should hold integers.
 Using an istream_iterator read the input file.
 Using ostream_iterators, write the odd numbers into the first output file.
 Each value should be followed by a space.
 Write the even numbers into the second file.
 Each of these values should be placed on a separate line.
 
 >> In this version I have used versin to tidy up the output
 
*/

#include <fstream>
#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char **argv)
{
    // check for input and output files
    if (argc < 2) {
        std::cerr << "No input file provided – closing programme..." << std::endl;
        return -1;
    }
    
    // too many arguments
    if (argc > 4) {
        std::cerr << "Too many files – closing programme..." << std::endl;
        return -1;
    }
    
    // open file of integers
    std::ifstream in(argv[1]);
    
    // print error if file not founds
    if (!in.is_open()) {
        std::cerr << "File not found – closing programme..." << std::endl;
        return -1;
    }
    
    // read file contents to stream iterator
    std::istream_iterator<int> in_iter(in), eof;
    
    // store stream to vector for sorting
    std::vector<int> ivec(in_iter, eof);
    
    // odds to one side, evens to anotehr
    std::partition(ivec.begin(), ivec.end(), [] (const int &x) { return x % 2; } );
    
    // find the position at which odds end and evens start
    auto evens_start = std::find_if_not(ivec.begin(), ivec.end(), [] (const int &x) { return x % 2; } );
    
    // tidy up partitions using "breaker" from above
    std::sort(ivec.begin(), evens_start);
    std::sort(evens_start, ivec.end());
    
    // create output files
    std::ofstream out_odds(argv[2]), out_evens(argv[3]);
    
    // create output streams for odd and even numbers with their unique delimiters
    std::ostream_iterator<int> out_iter_odds(out_odds, " "), out_iter_evens(out_evens, "\n");
    
    // copy contents of vector to appropriate output files
    std::copy(ivec.begin(), evens_start, out_iter_odds);
    std::copy(evens_start, ivec.end(), out_iter_evens);
    
    return 0;
}
