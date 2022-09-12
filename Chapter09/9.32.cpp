// Exercise 9.32:
/*
 In the program onpage 354 would it be legal to write the call to insert as follows?
 If not, why not?
 
 iter = vi.insert(iter, *iter++);
 
 >> if iv = { 1, 2, 3, 4, 5 }
 >> The above code will insert the number "1" before the first element "1", and continue to do so, almost as if iv.begin() is constantly being shifted one place to the right every iteration.
 >> I would say the code is "legal", but you run the risk of an indefinite loop if using something like
 >> while (iter != iv.end())
 >> I have attached an example below that produces the following output over 5 iterations
 
 1 2 3 4 5
 1 1 2 3 4 5
 1 1 1 2 3 4 5
 1 1 1 1 2 3 4 5
 1 1 1 1 1 2 3 4 5
 1 1 1 1 1 1 2 3 4 5
 
*/

#include <vector>
#include <iostream>

int main()
{
    std::vector<int> ivec = {1, 2, 3, 4, 5};
    
    for (const auto &e : ivec)
        std::cout << e << " ";
    std::cout << std::endl;
    
    for (auto iter = ivec.begin(); iter != ivec.begin() + 5; ++iter) {
        iter = ivec.insert(iter, *iter++);
        for (const auto &e : ivec)
            std::cout << e << " ";
        std::cout << std::endl;
    }
    
    return 0;
}
