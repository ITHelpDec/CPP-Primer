// Exercise 10.33:
/*
 Write a program that takes the names of an input file and two output files.
 
 The input file should hold integers.
 Using an istream_iterator read the input file.
 Using ostream_iterators, write the odd numbers into the first output file.
 Each value should be followed by a space.
 Write the even numbers into the second file.
 Each of these values should be placed on a separate line.
 
 >> It might be worth making use of a std::vector<int> to sort the numbers prior to file insertion
 >> I will do another version using vectors
 
*/

#include <fstream>
#include <iterator>
#include <iostream>

bool isOdd(const int &x, const int &y)
{
    return x % 2;
}

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
    
    // create output files
    std::ofstream out_odds(argv[2]), out_evens(argv[3]);
    
    // create output streams for odd and even numbers
    std::ostream_iterator<int> out_iter_odds(out_odds, " "), out_iter_evens(out_evens, "\n");
    
    // create output file streams for odd and even numebrs
    std::for_each(in_iter, eof, [&] (const int &x) { return x % 2 ? out_iter_odds = x : out_iter_evens = x ; } );
    
    return 0;
}
