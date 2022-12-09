// Exercise 16.21:
/*
 Write your own version of DebugDelete.
*/

#include <iostream>
#include <memory>
#include <string>

class DebugDelete {
public:
    DebugDelete(std::ostream &os = std::cerr) : os_(os) { }
    
    template <typename T> void operator() (T *p) const
    {
        os_ << "deleting unique_ptr" << std::endl;
        delete p;
    }
private:
    std::ostream &os_;
};

int main()
{
    double *p = new double;     // creates new double pointer
    DebugDelete d;              // creates DebugDelete object
    d(p);                       // calls "()" operator, which deletes "p"
    
    int *ip = new int;          // creates new int pointer
    DebugDelete()(ip);          // delete "ip" using temporary DebugDelete object
    
    // creates then immediately deletes unique_ptr of type "int"
    std::unique_ptr<int, DebugDelete> up(new int, DebugDelete());
    
    // creates then immediately deletes unique_ptr of type "std::string"
    std::unique_ptr<std::string, DebugDelete> sp(new std::string, DebugDelete());
    
    return 0;
}
