// Exercise 9.49:
/*
 A letter has an ascender if, as with d or f, part of the letter extends above the middle of the line.
 A letter has a descender if, as with p or g, part of the letter extends below the line.
 Write a program that reads a file containing words and reports the longest word that contains neither ascenders nor descenders.
 
 >> Could probably design a clause if no word is produced at all
*/

#include <string>
#include <iostream>

void longestword(const std::string &word, const std::string &neiascnordesc)
{
    std::string::size_type pos = 0;
    
    std::cout << "The longest word with neither ascenders nor descenders is \"";
    while ( (pos = word.find_first_of(neiascnordesc,pos)) != std::string::npos) {
        std::cout << word[pos];
        ++pos;
    }
    std::cout <<"\"" << std::endl;
}

int main()
{
    // initilaise letters that are neither ascenders nor descenders
    std::string neiascnordesc = "acemnorsuvwxz";
    
    // create test string
    std::string word = "manbearpig";
    
    // run function
    longestword(word, neiascnordesc);
    
    return 0;
}
