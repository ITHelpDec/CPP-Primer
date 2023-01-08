// Exercise 19.14:
/*
 Is the following code legal?
 If so, what does it do?
 If not, why?
 
 >> Yes (see comments below)
*/

#include <string>
#include <iostream>

class Screen {
public:
    typedef std::string::size_type pos;
    
    char get_cursor() const { return contents_[cursor_]; }
    char get() const { return 'a'; }
    char get(pos height, pos width) const { return 'z'; }
private:
    std::string contents_;
    pos cursor_;
    pos height_, width_;
};

int main()
{
    // §19.4.2 – "Pointers to Member Functions" – pg. 838
    // "pmf" is a pointer that can point to a Screen member function that is const
    // itreturns a char and takes no argument
    auto pmf = &Screen::get_cursor;
    
    // calls Screen::get() const
    // however, this might not be what we want...
    pmf = &Screen::get;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // if we want to return the overloaded function "we must distinguish...
    // ...which function we want explicitly", remembering to include const's
    char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
    
    // calls Screen::get(pos, pos) const
    pmf2 = &Screen::get;
    
    // both return "1" – not what we want
    std::cout << "pmf:  " << pmf  << std::endl;
    std::cout << "pmf2: " << pmf2 << std::endl;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // call member functions through a pointer-to-member
    Screen myScreen, *pScreen = &myScreen;
    char c1 = (pScreen->*pmf)();
    char c2 = (pScreen->*pmf2)(6, 9);
    
    // returns results from functions
    std::cout << "c1: " << c1 << std::endl;
    std::cout << "c2: " << c2 << std::endl;
    
    return 0;
}
