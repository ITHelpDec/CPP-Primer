// Exercise 9.22:
/*
 Assuming iv is a vector of ints, what is wrong with the following program?
 How might you correct the problem(s)?
 
 vector<int>::iterator iter = iv.begin(),
 mid = iv.begin() + iv.size()/2;
 while (iter != mid)
    if (*iter == some_val)
        iv.insert(iter, 2 * some_val);
 
 >> If the intention of the programme is to add an element to the beginning of the vector when a condition is met then I would re-write the programme as follows
 */

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> iv = {1, 3, 5, 7, 9};
    std::cout << "iv: ";
    for (const auto &e : iv)
        std::cout << e << " ";
    
    int some_val = 1;
    
    std::vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size()/2;
    
    std::cout << std::endl << "Running while loop up until middle of vector..." << std::endl;;
    while (iter != mid) {
      if (*iter == some_val) {
          std::cout << "Value (" << *iter << ") was found in the first position." << std::endl << "Inserting element at front of vector, twice the value of " <<  *iter << ".." << std::endl;
          // *iter = 1, iv.begin() = 1
          iv.insert(iter, 2 * some_val);
          // will only run if the first element in iv is some_val (iterator never increases)
          // iv = {2, 1, 2, 3, 4, 5}
          // *iter = 1, iv.begin() = 2
          
          // iterators must be added for both success and failure
          //
          ++iter;
      }
        ++iter;
    }
    
    std::cout << "iv: ";
    for (const auto &e : iv)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
     return 0;
}
