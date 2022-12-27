// Exercise 17.38:
/*
 Extend your program from the previous exercise to print each word you read onto its own line.
 
 >> Doesn't quite work the way I want
 >> Includes the '\n' character from the source (would prefer it weren't there)
 
*/

#include <fstream>
#include <iostream>
#include <climits>

int main()
{
    // 357 characters in file
    std::ifstream file("storyDataFile");
    
    if (!file) {
        std::cerr << "Unable to open file.\n" << std::endl; return -1;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    // 16 chars
    // smaller buffer
    char word_sink[2<<4];

    while (file) {
        // ' ' delimiter for each word
        file.getline(word_sink, 2<<4, ' ');
        std::cout.write(word_sink, file.gcount()) << "\n";
    }
    
    file.close();
    
    return 0;
}
