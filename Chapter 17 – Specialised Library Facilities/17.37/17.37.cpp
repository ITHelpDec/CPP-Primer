// Exercise 17.37:
/*
 Use the unformatted version of getline to read a file a line at a time.
 Test your program by giving it a file that contains empty lines as well as lines that are longer than the character array that you pass to getline.
 
 >> This is a really poorly-worded question.
 >> An example of get() or getline() member functions in use would have been more helpful.
 
*/

#include <fstream>
#include <iostream>

int main()
{
    // 357 characters in file
    std::ifstream file("storyDataFile");
    
    if (!file) {
        std::cerr << "Unable to open file.\n" << std::endl; return -1;
    } std::cout << "File opened successfully.\n" << std::endl;
    
    // 64 chars
    char line_sink[2<<6];
    
    while (file) {
        file.getline(line_sink, 2<<6, '\n');
        // use of .gcount() to print out only as many characters as were last read
        std::cout.write(line_sink, file.gcount()) << "\n";
    }
    
    file.close();
    
    return 0;
}
