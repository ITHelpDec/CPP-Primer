// Exercise 14.40:
/*
 Rewrite the biggies function from § 10.3.2 (p. 391) to use function- object classes in place of lambdas.
*/

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class IsShorter {
public:
    bool operator() (const std::string &a, const std::string &b) { return a.size() < b.size(); }
private:
};

class IsAtLeast {
public:
    // think of constructors as capture list in a lambda function
    IsAtLeast(std::vector<std::string>::size_type sz) : sz(sz) { }
    
    bool operator() (const std::string &a) { return a.size() >= sz; }
private:
    std::vector<std::string>::size_type sz;
};

class PrintString {
public:
    void operator() (const std::string &s) { std::cout << s << " "; }
private:
};

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type &&sz)
{
    // elimDups(words);
    
    // std::stable_sort(words.begin(), words.end(), [](const std::string &a, const std::string &b) { return a.size() < b.size();});
    std::stable_sort(words.begin(), words.end(), IsShorter());

    // auto wc = find_if(words.begin(), words.end(), [sz](const std::string &a) { return a.size() >= sz; });
    auto wc = find_if(words.begin(), words.end(), IsAtLeast(sz));
    auto count = words.end() - wc;
    
    // std::cout << count << " " << make_plural(count, "word", "s") << " of length " << sz << " or longer" << std::endl;
    std::cout << count << " " << (count == 1 ? "word" : "words") << " of length " << sz << " or longer" << std::endl;
    
    // std::for_each(wc, words.end(), [](const std::string &s) { std::cout << s << " ";}); std::cout << std::endl;
    std::for_each(wc, words.end(), PrintString());
    
    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> svec = { "man" , "bear", "pig" };
    
    biggies(svec, 4);
    
    return 0;
}
