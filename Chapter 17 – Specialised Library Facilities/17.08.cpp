// Exercise 17.08:
/*
 What would happen if we passed Sales_data() as the third parameter to accumulate in the last code example in this section?
 
 >> Sales_data appears to call the synthesised default constructor as opposed to our explicit std::string constructor
 
 Sales_data(const std::string &s) : bookNo(s) { }
 
 >> The programme still runs as it did previously.
 
 >> Also, bear in mind std::accumulate(It, It, starting_value)'s third variable is its starting value, ..
 >> ...so as long as htat is 0, the programme will run as intended.
*/

// from exercise 16.62
#include "Sales_data.hpp"

#include <vector>
#include <algorithm>
#include <numeric>

typedef std::vector<Sales_data> SDVec;

struct Matches {
    Matches(const SDVec::size_type &sz, const SDVec::const_iterator &cbegin, const SDVec::const_iterator &cend)
        : number_(sz), cbegin_(cbegin), cend_(cend) { }
    
    SDVec::size_type number_;
    SDVec::const_iterator cbegin_;
    SDVec::const_iterator cend_;
};

bool compareISBN(const Sales_data &lhs, const Sales_data &rhs) { return lhs.isbn() < rhs.isbn(); }

std::vector<Matches> findBook(const std::vector<SDVec> &files, const std::string &book) {
    std::vector<Matches> ret;
    
    for (auto it = files.cbegin(); it != files.cend(); ++it) {
        auto found = std::equal_range(it->cbegin(), it->cend(), book, compareISBN);
        if (found.first != found.second)
            ret.push_back(Matches(it - files.cbegin(), found.first, found.second));
    }
    
    return ret;
}

void reportResults(std::istream &is, std::ostream &os, const std::vector<SDVec> &files) {
    std::string s;
    std::cout << "Please enter an ISBN number: ";
    while (is >> s) {
        auto trans = findBook(files, s);
        if (trans.empty()) {
            std::cout << s << " not found in any stores." << std::endl;
            continue;
        }
        for (const auto &store : trans) {
            os << "Store " << store.number_ << " sales:"
               // << std::accumulate(store.cbegin_, store.cend_, Sales_data(s))
               << std::accumulate(store.cbegin_, store.cend_, Sales_data())
               << std::endl;
        }
    }
}

int main()
{
    std::vector<SDVec> files = {
        { Sales_data("123-456-789-X", 20, 100) },
        { Sales_data("123-456-789-Y", 20, 120) },
        { Sales_data("123-456-789-Z", 20, 180) },
        { Sales_data("123-456-789-X", 20, 200) },
    };
    
    reportResults(std::cin, std::cout, files);
    
    return 0;
}
