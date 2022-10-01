// Exercise 9.51:
/*
 Write a class that has three unsigned members representing year, month, and day.
 Write a constructor that takes a string representing a date.
 Your constructor should handle a variety of date formats, such as January 1, 1900, 1/1/1900, Jan 1, 1900, and so on.
*/

#include <string>
#include <iostream>

class Date {
    
    // friend member function to print out variations like dd/mm/yyyy
    
public:
    // (2) constructor that takes a string
    Date(const std::string &s);
    
    // member functions to convert assign portions of string to unsigned month, day and year
    
private:
    // (1) three unsigned representing year, month and day
    unsigned month;
    unsigned day;
    unsigned year;
};

int main()
{
    Date date1("January 1, 1900");
    Date date2("1/1/1990");
    Date date3("Jan 1, 1900");
    
    return 0;
}
