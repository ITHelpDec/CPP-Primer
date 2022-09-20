// Exercise 9.28:
/*
 Write a function that takes a forward_list<string> and two additional string arguments.
 The function should find the first string and insert the second immediately following the first.
 If the first string is not found, then insert the second string at the end of the list.
 */

#include <forward_list>
#include <string>
#include <string>
#include <iostream>

void addStrings(std::forward_list<std::string> &flist, const std::string &s1, const std::string &s2) {
    //create iterators
    auto prev = flist.before_begin();
    auto curr = flist.begin();
    
    while (curr != flist.end()) {
        if (*curr == s1) {
            flist.insert_after(curr, s2);
            return;
        }
        ++prev, ++curr;
    }
    flist.insert_after(prev, s2);
}

int main()
{
    std::forward_list<std::string> flistTest = {"half", "man", "bear", "pig"};
    
    addStrings(flistTest, "dog", "man bear pig");
    
    for (const auto &e : flistTest)
        std::cout << e << " ";
    
    std::cout << std::endl;
    
    return 0;
}
