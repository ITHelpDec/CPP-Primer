// Exercise 17.34:
/*
 Write a program that illustrates the use of each manipulator in Tables 17.17 (p. 757) and 17.18.
*/

#include <iostream>
#include <iomanip>
#include <fstream>

int main()
{
    std::cout << "bools:\n"
              << ">>> " << true << " " << false << "\n"
              << std::boolalpha << ">>> " << true << " " << false << "\n"
              << std::noboolalpha << ">>> " << true << " " << false << "\n"
              << std::endl;
    
    std::cout << "bases:\n"
              << std::hex << ">>> " << 20 << " " << 1024 << "\n"
              << std::showbase << ">>> " << 20 << " " << 1024 << "\n"
              << std::noshowbase << ">>> " << 20 << " " << 1024 << "\n"
              << std::dec << std::endl;
    
    std::cout << "points:\n"
              << ">>> " << 10.0 << "\n"
              << std::showpoint << ">>> " << 10.0 << "\n"
              << std::noshowpoint << ">>> " << 10.0 << "\n"
              << std::endl;
    
    std::cout << "notational bases:\n"
              << std::hex << ">>> " << 20 << " " << 1024 << "\n"
              << std::hexfloat << ">>> " << 20 << " " << 1024 << "\n"
              << std::oct << ">>> " << 20 << " " << 1024 << "\n"
              << std::scientific << ">>> " << 20 << " " << 1024 << "\n"
              << std::defaultfloat << ">>> " << 20 << " " << 1024 << "\n"
              << std::endl;
    
    int i = -16;
    double d = 3.14159;
    
    std::cout << "fills and allignment:\n";
    std::cout << ">>> i: " << std::setw(12) << i << " next col" << "\n"
              << ">>> d: " << std::setw(12) << d << " next col" << "\n";
    
    std::cout << std::left
              << ">>> i: " << std::setw(12) << i << " next col" << "\n"
              << ">>> d: " << std::setw(12) << d << " next col" << "\n"
              << std::right;
    
    std::cout << std::right
              << ">>> i: " << std::setw(12) << i << " next col" << "\n"
              << ">>> d: " << std::setw(12) << d << " next col" << "\n";
    
    std::cout << std::internal
              << ">>> i: " << std::setw(12) << i << " next col" << "\n"
              << ">>> d: " << std::setw(12) << d << " next col" << "\n";
    
    std::cout << std::setfill('#')
              << ">>> i: " << std::setw(12) << i << " next col" << "\n"
              << ">>> d: " << std::setw(12) << d << " next col" << "\n"
              << std::setfill(' ');
    
    std::ifstream file("no-skipws");
    
    if (!file) {
        std::cerr << "Unable to open input file." << std::endl; return -1;
    } std::cout << "File opened successfully." << std::endl;
    
    char ch;
    
    std::cout << "\n>>> std::skipws <<<\n";
    while (file >> ch) { std::cout << ch; } std::cout << std::endl;
    
    // clear flags (including eofbit), then return to beginning of file
    file.clear(); file.seekg(0);
    
    std::cout << "\n>>> std::noskipws <<<\n";
    while (file >> std::noskipws >> ch) { std::cout << ch; } std::cout << std::endl;
    
    file.close();
    
    // other features include:
    // std::unitbuf
    // std::nounitbuf
    // std::flush
    // std::ends
    
    return 0;
}
