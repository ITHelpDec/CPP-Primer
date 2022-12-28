// Exercise 18.05:
/*
 Given the following exception types and catch clauses, write a throw expression that creates an exception object that can be caught by each catch clause:
 
 // An easier question than it seems, but throwing errors in the try feels quite abstract – more examples should be given of real-life implementation to gain something meaningful from this exercise.
 
*/

// // (a)
// class exceptionType { };
// catch (exceptionType *pet) { }

// // (b)
// catch(...) { }

// // (c)
// typedef int EXCPTYPE;
// catch(EXCPTYPE) { }

#include <stdexcept>
#include <iostream>
#include <string>

// (a)
class exceptionType {
public:
    void setNumberOfLegs(std::size_t legs)
    {
        if (legs > 4) {
            error_ = "legs";
            throw this;
        }
        legs_ = legs;
    }
    
    void feed16LitresofWater()
    {
        throw std::overflow_error("\n>>> woof woof! doggie has overflowed! you couldn't catch it in time!");
    }
    
    std::string what() { return error_; }
    
private:
    std::size_t legs_ = 4;
    
    std::string error_;
};

int main()
{
    exceptionType dog;
    
    try {
        dog.setNumberOfLegs(4);
        dog.feed16LitresofWater();
    } // (a)
      catch (exceptionType *pet) {
        std::cerr << "error: " << pet->what() << "\n>>> woof woof! too many legs" << std::endl;
        return -1;
    
    // probably a better idea to create specfic catches instead of catch-all
    // } catch (std::overflow_error e) {
       // std::cerr << "error: " << e.what() << std::endl;
          
    } // (b)
      catch (...) {
        throw;
    }
    
    // (c)
    typedef int EXCTYPE;
    
    try {
        throw 42;
    } catch (EXCTYPE) {
        std::cerr << "error: \"EXCTYPE\"" << std::endl;
        return -1;
    }
    
    return 0;
}
