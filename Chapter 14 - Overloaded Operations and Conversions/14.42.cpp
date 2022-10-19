// Exercise 14.42:
/*
 Using library function objects and adaptors, define an expression to
 
 (a) Count the number of values that are greater than 1024
 (b) Find the first string that is not equal to "pooh"
 (c) Multiply all values by 2
 
*/

#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

int main()
{
    // (a)
    // std::bind() from Chapter 10 is instrumental in this working
    // std::greater<> performs "return lhs >= rhs;"
    // we then use placeholders to imply the first argument (lhs) and explicitly declare the second (rhs)
    // i.e. return lhs >= 1023
    std::vector<int> ivec = { 1024, 1021, 1025, 1026, 1027 };
    auto greater = std::count_if(ivec.begin(), ivec.end(), std::bind(std::greater<int>(), std::placeholders::_1, 1024));
    std::cout << "(a): " << greater << " " << (greater == 1 ? "number was" : "numbers were") << " found greater than 1024." << std::endl;
    
    // (b)
    // std::equal_to performs "lhs == rhs", so again we use placeholders
    std::vector<std::string> svec = { "pooh", "pooh", "pooh", "pooh", "po0h", "pooh" };
    auto first_not_pooh = std::find_if_not(svec.begin(), svec.end(), std::bind(std::equal_to<std::string>(), std::placeholders::_1, "pooh"));
    std::cout << "(b) The first string that isn't \"pooh\" is \"" << *first_not_pooh << "\", found in position svec[" << first_not_pooh - svec.begin() << "]" << std::endl;
    
    // (c)
    // std::multiplies<> performs lhs * rhs
    std::cout << "ivec: ";
    for (const auto &e : ivec) {
        std::cout << e << " ";
    } std::cout << " (before multiplication)" << std::endl;
    
    // std::for_each() had no effect
    // std::for_each(ivec.begin(), ivec.end(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    
    // std::transform() allows us to modify the vector as we traverse through it
    std::transform(ivec.begin(), ivec.end(), ivec.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));
    
    std::cout << "ivec: ";
    for (auto &e : ivec) {
        std::cout << e << " ";
    } std::cout << " (after multiplication)" << std::endl;
    
    return 0;
}
