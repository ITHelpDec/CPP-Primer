// Exercise 13.39:
/*
 We did not use copy and swap to define the Message assignment operator.
 Why do you suppose this is so?
*/

// simplified implementatin of the emory allocation strategy for a vector-like class

#include <allocator>
#include <vector>

class StrVec {
    
    
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    
private:
    std::vector<int> *elements;
    std::vector<int>::iterator *first_free;
    std::vector<int>::iterator *cap;
    
    static
    
};
