// Exercise 9.34:
/*
 Assuming vi is a container of ints that includes even and odd values, predict the behavior of the following loop.
 After you’ve analyzed this loop, write a program to test whether your expectations were correct.
 
 iter = vi.begin();
 while (iter != vi.end())
    if (*iter % 2)
        iter = vi.insert(iter, *iter);
    ++iter;
 
*/

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> vi = { 1, 2, 3, 4, 5, 6 };
    
    std::cout << "vi: ";
    for (const auto &e : vi)
        std::cout << e << " ";
    std::cout << std::endl;
    
    // the following loop will add 1's to the beginning of the vector indefinitely
    /*
    auto iter = vi.begin();
    while (iter != vi.end()) {
        if (*iter % 2)
            iter = vi.insert(iter, *iter);
        ++iter;
    }
     */
    
    // I have created a finite for loop to test this below, with the follwoing output
    // vi: 1 2 3 4 5 6
    // vi: 1 1 2 3 4 5 6
    // vi: 1 1 1 2 3 4 5 6
    // vi: 1 1 1 1 2 3 4 5 6
    // vi: 1 1 1 1 1 2 3 4 5 6
    // vi: 1 1 1 1 1 1 2 3 4 5 6
    for (auto iter = vi.begin(); iter != vi.begin() + 5; ++iter) {
        if (*iter % 2)
            iter = vi.insert(iter, *iter);
        
        std::cout << "vi: ";
        for (const auto &e : vi)
            std::cout << e << " ";
        std::cout << std::endl;
    }

    return 0;
}
