// Exercise 12.21:
/*
 We could have written StrBlobPtr’s deref member as follows:
 
 //
 // std::string& deref const { return (*check(curr, "dereference past end"))[curr]; }
 //
 
 Which version do you think is better and why
*/

#include <string>

class StrBlobPtr {
    /*...*/
public:
    /*...*/
    
    // version 1
    // version 1 is cleaner for the class design and allows us to expand on the funciton further down
    // I like the idea of a class being a brief overview of the programme that we can then expand on later with more detailed functions
    std::string& deref() const;
    
    // version 2
    // version 2 is more verbose and to the point, but might run make the code appear too busy too early on
    std::string& deref const { return (*check(curr, "dereference past end"))[curr]; }
    
    // I think the answer will boil down to personal preference and legibility
    
    /*...*/
private:
    /*...*/
};
