// Exercise 17.09:
/*
 Explain the bit pattern each of the following bitset objects contains:
*/

#include <bitset>
#include <string>
#include <iostream>

int main()
{
    // (a)
    std::bitset<64> bitvec(32);
    // bitvec will be 64 bits wide, converting 32 into binary
    // 32 16 8 4 2 1
    // 1  0  0 0 0 0
    // resulting bitvec should be:
    // 0000000000000000000000000000000000000000000000000000000000100000
    std::cout << bitvec << std::endl;
    
    
    // (b)
    std::bitset<32> bitvec1(1010101);
    // bitvec should be 32 bits wide, converting 1010101 into a bitvec
    // resulting bitvec should be:
    // 00000000000011110110100110110101
    std::cout << bitvec1 << std::endl;
    
    // (c)
    std::string bstr;
    std::cout << "Insert binary string: ";
    std::cin >> bstr;
    std::bitset<8> bitvec2(bstr);
    // std::cin takes string and inserts 8 bits from that string
    // elements beyond s[8] will be ignored
    
    // 10101010101010101111 produces
    // 10101010
    
    std::cout << bitvec2 << std::endl;
}
