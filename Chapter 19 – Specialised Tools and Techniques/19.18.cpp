// Exercise 19.18:
/*
 Write a function that uses count_if to count how many empty strings there are in a given vector.
*/

#include <vector>
#include <string>
#include <iostream>
// #include <functional>

int main()
{
    std::vector<std::string> svec = { "half", "man", "", "half", "bear", "", "half", "pig" };
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Introducing \"17 ways to skin a cat\"\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Our vector:\n";
    for (const std::string &s : svec) {
        std::cout << "\"" << s << "\" ";
    } std::cout << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using a lambda function...\n";
    std::cout << "number of empty strings: "
    << std::count_if(svec.begin(), svec.end(), [] (const std::string &s) { return s == ""; } )
    << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::function<>()...\n";
    std::function<bool (const std::string&)> fcn = &std::string::empty;
    std::cout << "number of empty strings: "
    << std::count_if(svec.begin(), svec.end(), fcn)
    << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::mem_fn...\n";
    std::cout << "number of empty strings: "
    << std::count_if(svec.begin(), svec.end(), std::mem_fn(&std::string::empty))
    << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    std::cout << "Using std::bind...\n";
    std::cout << "number of empty strings: "
    << std::count_if(svec.begin(), svec.end(),
                     std::bind(&std::string::empty, std::placeholders::_1))
    << "\n\n";
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    return 0;
}

// output:
// Introducing "17 ways to skin a cat"
//
// Our vector:
// "half" "man" "" "half" "bear" "" "half" "pig"
//
// Using a lambda function...
// number of empty strings: 2
//
// Using std::function<>()...
// number of empty strings: 2
//
// Using std::mem_fn...
// number of empty strings: 2
//
// Using std::bind...
// number of empty strings: 2
//
// Program ended with exit code: 0
