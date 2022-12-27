// Exercise 17.39:
/*
 Write your own version of the seek program presented in this section.
 
 >> Finally, we learn to read and write in the same file.
 >> ...and it only took 17 chapters :)
*/

#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::fstream file("file", std::fstream::ate | std::fstream::in | std::fstream::out);
    
    if (!file) {
        std::cerr << "Unable to open file." << std::endl; return EXIT_FAILURE;
    } std::cout << "File opened succesfully." << std::endl;
    
    auto end_mark = file.tellp();
    file.seekg(0, std::fstream::beg);
    
    std::size_t count = 0;
    std::string line;
    
    while (file && file.tellg() != end_mark && std::getline(file, line)) {
        count += line.size() + 1;
        
        auto mark = file.tellg();
        
        file.seekp(0, std::fstream::end);
        file << count;
        if (mark != end_mark) { file << " "; }
        
        file.seekg(mark);
    }
    
    file.seekp(0, std::fstream::end);
    file << "\n";
    
    file.close();
    
    return 0;
}
