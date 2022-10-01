// Exercise 10.04:
/*
 Assuming v is a vector<double>, what, if anything, is wrong with
 calling accumulate(v.cbegin(), v.cend(), 0)?
 
 >> If the final argument is 0 instead of 0.0, the values from the vector will be truncated before producing the final result i.e.
 >> accumint(dvec)  = 15
 >> accumdoub(dvec) = 16.5
*/

#include <vector>
#include <numeric>
#include <iostream>

void accumint(const std::vector<double> &dvec)
{
    std::cout << std::accumulate(dvec.cbegin(), dvec.cend(), 0) << std::endl;
}

void accumdoub(const std::vector<double> &dvec)
{
    std::cout << std::accumulate(dvec.cbegin(), dvec.cend(), 0.0) << std::endl;
}

int main()
{
    // create vector of ints
    std::vector<double> dvec = { 0.0, 1.1, 2.2, 3.3, 4.4, 5.5 };
    
    // call functions
    accumint(dvec);
    accumdoub(dvec);
    
    return 0;
}
