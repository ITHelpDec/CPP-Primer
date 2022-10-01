// Exercise 9.50:
/*
 Write a program to process a vector<string>s whose elements represent integral values.
 Produce the sum of all the elements in that vector.
 Change the program so that it sums of strings that represent floating-point values.
*/

#include <vector>
#include <string>
#include <iostream>

void sumVec(const std::vector<std::string> &svec)
{
    int sum = 0;
    
    for (const auto &e : svec)
        sum += stoi(e);
    
    std::cout << "Sum of vector elements as ints: " << sum << std::endl;
}

void sumVecfloat(const std::vector<std::string> &svec)
{
    float sum = 0.0;
    
    for (const auto &e : svec)
        sum += stof(e);
    
    std::cout << "Sum of vector elements as floats: " << sum << std::endl;
}

int main()
{
    std::vector<std::string> svec = { "1", "2", "3", "4", "5" };
    std::vector<std::string> svecf = { "1.11", "2.22", "3.33", "4.44", "5.55" };
    
    sumVec(svec);
    sumVecfloat(svecf);
    
    return 0;
}
