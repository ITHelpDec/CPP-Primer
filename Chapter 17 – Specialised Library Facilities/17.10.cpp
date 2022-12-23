// Exercise 17.10:
/*
 Using the sequence 1, 2, 3, 5, 8, 13, 21, initialize a bitset that has a 1 bit in each position corresponding to a number in this sequence.
 Default initialize another bitset and write a small program to turn on each of the appropriate bits.
*/

#include <bitset>
#include <vector>
#include <iostream>

std::bitset<32> fibonacciBits() {
    // lol, fibonacci
    std::vector<int> seq = { 1, 2, 3, 5, 8, 21 };
    std::bitset<32> bitvec;
    for (const auto &pos : seq) { bitvec.set(pos); }
    return bitvec;
}

int main()
{
    // painful
    std::bitset<32> bitvec("00000000001000000000000100101110");
    std::cout << bitvec << std::endl;
    
    std::cout << fibonacciBits() << std::endl;
    
    return 0;
}
