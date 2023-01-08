// Exercise 19.17:
/*
 Define a type alias for each distinct Screen member function type.
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
    std::string contents_ = "manbearpig";
    pos cursor_ = 42;
    pos height_ = 6, width_ = 9;
};

int main()
{
    Screen myScreen;
    
    // if we use the template from pg. 839 as a reference...
    // using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
    // Action get = &Screen::get;
    // Screen& action(Screen&, Action1 = &Screen::get);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // "Screen::get_cursor() const" or "Screen:get() const"
    using Action1 = char (Screen::*)() const;
    Action1 get_cursor = &Screen::get_cursor;
    Action1 get1 = &Screen::get;
    
    Screen& action1(Screen&, Action1 = &Screen::get);
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    // Screen::get(pos, pos) const
    using Action2 = char (Screen::*)(Screen::pos, Screen::pos) const;
    Action2 get2 = &Screen::get;
    
    Screen& action2(Screen&, Action2 = &Screen::get);
    
    return 0;
}
