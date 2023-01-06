// Exercise 19.12:
/*
 Define a pointer to member that can point to the cursor member of class Screen.
 Fetch the value of Screen::cursor through that pointer.
*/

#include <string>
#include <iostream>

class Screen {
public:
    typedef std::string::size_type pos;
    
    char get_cursor() const { return contents_[cursor_]; }
    char get() const;
    char get(pos height, pos width) const;
    
    static const std::string Screen::*data() { return &Screen::contents_; }
    
    // public helper function to return position of cursor
    static const pos Screen::*exercise() { return &Screen::cursor_; }
private:
    std::string contents_;
    pos cursor_ = 42;
    pos height_, width_;
};

int main()
{
    // again, cursor_ is a private member...
    // auto ptm = &Screen::cursor_;
    
    // need public helper function (created above)
    
    // use of public helper function return position of cursor
    std::cout << "cursor: " << Screen().*Screen::exercise() << std::endl;
    
    return 0;
}
