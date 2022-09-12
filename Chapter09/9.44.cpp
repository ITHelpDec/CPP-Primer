// Exercise 9.44:
/*
 Rewrite the previous function using an index and replace.
 
 >> Similar issues with the letter r
 >> using a "pos" with substr() proved useful this time round
 >> using replace is much tidier than erase and insert
 
*/

#include <string>
#include <iostream>

void replaceAbbrev(std::string &s, const std::string &oldVal, const std::string &newVal)
{
    for (std::string::size_type pos = 0; pos != s.size(); /* no generic iterator */ )
    {
        if (s.substr(pos, oldVal.size()) == oldVal) {
            s.replace(pos, oldVal.size(), newVal);
            pos += newVal.size();
        }
        else
            ++pos;
    }
}

int main()
{
    std::string s = "r u going thru the town tho?";
    
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "r", "are");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "u", "you");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "thru", "through");
    std::cout << s << std::endl;
    
    replaceAbbrev(s, "tho", "though");
    std::cout << s << std::endl;
    
    return 0;
}
